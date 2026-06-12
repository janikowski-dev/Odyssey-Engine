from __future__ import annotations

import argparse
import os
import re
import sys
from dataclasses import dataclass, field
from typing import Optional

def _load_libclang(explicit: Optional[str]) -> None:
    from clang import cindex

    candidates = []
    if explicit:
        candidates.append(explicit)
    if os.environ.get("REFLECTGEN_LIBCLANG"):
        candidates.append(os.environ["REFLECTGEN_LIBCLANG"])
    try:
        import clang as _clang_pkg
        bundled = os.path.join(os.path.dirname(_clang_pkg.__file__), "native", "libclang.so")
        candidates.append(bundled)
    except Exception:
        pass
    candidates += [
        "/usr/lib/llvm-18/lib/libclang.so",
        "/usr/lib/llvm-17/lib/libclang.so",
        "/usr/lib/x86_64-linux-gnu/libclang-18.so.1",
        "/usr/lib/x86_64-linux-gnu/libclang-1.so",
        "/Library/Developer/CommandLineTools/usr/lib/libclang.dylib",
    ]

    for path in candidates:
        if path and os.path.exists(path):
            try:
                cindex.Config.set_library_file(path)
                cindex.Index.create()
                return
            except Exception:
                cindex.Config.loaded = False
                continue

    try:
        cindex.Index.create()
    except Exception as exc:
        sys.exit(
            "error: could not locate a usable libclang. Pass --libclang "
            "/path/to/libclang.so or set $REFLECTGEN_LIBCLANG.\n"
            f"       underlying error: {exc}"
        )

@dataclass
class FieldMeta:
    min: Optional[float] = None
    max: Optional[float] = None
    options: Optional[list[str]] = None
    unknown: list[str] = field(default_factory=list)

    def has_storable(self) -> bool:
        return self.min is not None or self.max is not None or bool(self.options)


@dataclass
class Member:
    name: str
    qualified_member: str
    is_enum: bool
    enumerators: list[str]
    meta: FieldMeta


@dataclass
class Component:
    display_name: str
    qualified_type: str
    members: list[Member]
    source_include: str


def _split_top_level(text: str, sep: str = ",") -> list[str]:
    parts, depth, buf = [], 0, []
    for ch in text:
        if ch in "{([":
            depth += 1
        elif ch in "})]":
            depth = max(0, depth - 1)
        if ch == sep and depth == 0:
            parts.append("".join(buf).strip())
            buf = []
        else:
            buf.append(ch)
    if buf:
        parts.append("".join(buf).strip())
    return [p for p in parts if p != ""]


_TOKEN_RE = re.compile(r"^\s*([A-Za-z_]\w*)\s*(?:\{(.*)\}\s*)?$", re.DOTALL)


def _to_number(tok: str) -> Optional[float]:
    tok = tok.strip().rstrip("fF")
    try:
        return float(tok)
    except ValueError:
        return None


def parse_property_payload(payload: str, warn) -> FieldMeta:
    meta = FieldMeta()
    payload = payload.strip()

    if not payload:
        return meta

    for attr in _split_top_level(payload):
        m = _TOKEN_RE.match(attr)

        if not m:
            meta.unknown.append(attr)
            warn(f"could not parse property attribute {attr!r}")
            continue

        name, inner = m.group(1), m.group(2)
        args = _split_top_level(inner) if inner is not None else []

        key = name.lower()
        if key == "range":
            nums = [_to_number(a) for a in args]
            if len(nums) >= 2 and nums[0] is not None and nums[1] is not None:
                meta.min, meta.max = nums[0], nums[1]
                if len(nums) >= 3 and nums[2] is not None:
                    meta.step = nums[2]
            else:
                warn(f"Range expects at least min,max: {attr!r}")
        elif key == "min":
            v = _to_number(args[0]) if args else None
            if v is not None:
                meta.min = v
        elif key == "max":
            v = _to_number(args[0]) if args else None
            if v is not None:
                meta.max = v
        elif key == "options":
            meta.options = [a.strip().strip('"').strip("'") for a in args]
        else:
            meta.unknown.append(attr)
            warn(f"unknown property attribute {attr!r} (ignored)")

    return meta


def _annotations(cursor) -> list[str]:
    from clang.cindex import CursorKind
    return [c.spelling for c in cursor.get_children()
            if c.kind == CursorKind.ANNOTATE_ATTR]


def _qualified_name(cursor) -> str:
    from clang.cindex import CursorKind
    parts = []
    cur = cursor
    while cur is not None and cur.kind != CursorKind.TRANSLATION_UNIT:
        if cur.spelling:
            parts.append(cur.spelling)
        cur = cur.semantic_parent
    return "::".join(reversed(parts))


def _enum_decl_of(clang_type):
    from clang.cindex import TypeKind
    canon = clang_type.get_canonical()
    if canon.kind == TypeKind.ENUM:
        return canon.get_declaration()
    return None


def collect_components(tu, source_include: str, warn) -> list[Component]:
    from clang.cindex import CursorKind

    results: list[Component] = []

    def visit(cursor):
        for child in cursor.get_children():
            if child.kind in (CursorKind.STRUCT_DECL, CursorKind.CLASS_DECL):
                if child.is_definition() and "component" in _annotations(child):
                    comp = build_component(child, source_include, warn)
                    if comp is not None:
                        results.append(comp)

            if child.kind in (
                CursorKind.NAMESPACE,
                CursorKind.STRUCT_DECL,
                CursorKind.CLASS_DECL,
                CursorKind.TRANSLATION_UNIT,
                CursorKind.UNEXPOSED_DECL,
            ):
                visit(child)

    visit(tu.cursor)
    return results


def build_component(record, source_include: str, warn) -> Optional[Component]:
    from clang.cindex import CursorKind

    if record.kind == CursorKind.CLASS_TEMPLATE:
        warn(f"skipping template component {record.spelling}")
        return None

    qualified_type = _qualified_name(record)
    display_name = record.spelling
    members: list[Member] = []

    for f in record.get_children():
        if f.kind != CursorKind.FIELD_DECL:
            continue
        prop = next((a for a in _annotations(f) if a.startswith("property:")), None)
        if prop is None:
            continue

        if not f.spelling:
            warn(f"{display_name}: skipping anonymous field")
            continue
        if f.is_bitfield():
            warn(f"{display_name}::{f.spelling}: bitfields cannot be reflected (no &T::member)")
            continue
        if str(f.access_specifier) not in ("AccessSpecifier.PUBLIC", "AccessSpecifier.INVALID"):
            warn(f"{display_name}::{f.spelling}: non-public PROPERTY member cannot be " f"reflected from generated code")
            continue

        payload = prop[len("property:"):]
        meta = parse_property_payload(payload, warn)

        enum_decl = _enum_decl_of(f.type)
        is_enum = enum_decl is not None
        enumerators: list[str] = []
        if is_enum:
            enumerators = [e.spelling for e in enum_decl.get_children()
                           if e.kind == CursorKind.ENUM_CONSTANT_DECL]

        members.append(Member(
            name=f.spelling,
            qualified_member=f"{qualified_type}::{f.spelling}",
            is_enum=is_enum,
            enumerators=enumerators,
            meta=meta,
        ))

    if not members:
        warn(f"{display_name}: COMPONENT has no PROPERTY members (still registered)")

    return Component(
        display_name=display_name,
        qualified_type=qualified_type,
        members=members,
        source_include=source_include,
    )


def _fmt_double(v: float) -> str:
    if v == int(v):
        return f"{int(v)}.0"
    return repr(v)


def _cpp_string(s: str) -> str:
    return '"' + s.replace("\\", "\\\\").replace('"', '\\"') + '"'


def _meta_initializer(meta: FieldMeta) -> Optional[str]:
    parts = []
    if meta.options:
        parts.append(".Options = { " + ", ".join(_cpp_string(o) for o in meta.options) + " }")
    if meta.min is not None:
        parts.append(f".Min = {_fmt_double(meta.min)}")
    if meta.max is not None:
        parts.append(f".Max = {_fmt_double(meta.max)}")
    if not parts:
        return None
    return "Source::Serialization::FieldMeta{ " + ", ".join(parts) + " }"


def emit(components: list[Component], *, namespace: str, function: str,
         registry_type: str, header_name: str, warnings: list[str]) -> tuple[str, str]:

    includes = sorted({c.source_include for c in components})

    guard = re.sub(r"\W", "_", header_name).upper() + "_"
    hdr = [
        f"#ifndef {guard}",
        f"#define {guard}",
        "",
        "namespace Source::ECS { class Registry; }",
        "",
        f"namespace {namespace}",
        "{",
        f"    void {function}({registry_type}& Registry);",
        "}",
        "",
        f"#endif // {guard}",
        "",
    ]

    src = [
        "// This file has been generated using reflection."
    ]
    for w in warnings:
        src.append(f"// warning: {w}")
    src.append("")
    src.append(f'#include "{header_name}"')
    src.append("")
    src.append('#include "Serialization/TypeRegistry.h"')
    src.append('#include "Serialization/TypeBuilder.h"')
    src.append('#include "Serialization/FieldMeta.h"')
    src.append('#include "Serialization/ECSBinding.h"')
    src.append('#include "ECS/Registry.h"')
    src.append("")
    for inc in includes:
        src.append(f'#include "{inc}"')
    src.append("")
    src.append(f"namespace {namespace}")
    src.append("{")
    src.append(f"    void {function}({registry_type}& Registry)")
    src.append("    {")

    for comp in components:
        T = comp.qualified_type
        src.append(f"        // {comp.display_name}")
        src.append("        {")
        src.append(
            f"            auto Builder = Source::Serialization::TypeRegistry::Get()"
            f".Register<{T}>({_cpp_string(comp.display_name)});"
        )
        for m in comp.members:
            if m.is_enum:
                opts = m.meta.options if m.meta.options else m.enumerators
                opts_str = ", ".join(_cpp_string(o) for o in opts)
                src.append(
                    f"            Builder.EnumField(&{m.qualified_member}, "
                    f"{_cpp_string(m.name)}, {{ {opts_str} }});"
                )
            else:
                init = _meta_initializer(m.meta)
                if init:
                    src.append(
                        f"            Builder.Field(&{m.qualified_member}, "
                        f"{_cpp_string(m.name)}, {init});"
                    )
                else:
                    src.append(
                        f"            Builder.Field(&{m.qualified_member}, "
                        f"{_cpp_string(m.name)});"
                    )
        src.append("            Source::Serialization::BindECS(Builder, Registry);")
        src.append("        }")
    src.append("    }")
    src.append("}")
    src.append("")

    return "\n".join(hdr), "\n".join(src)


def make_include_path(input_path: str, roots: list[str]) -> str:
    norm = os.path.normpath(input_path)
    abspath = os.path.abspath(norm)
    best = None
    for r in roots:
        rabs = os.path.abspath(r)
        if abspath.startswith(rabs + os.sep):
            rel = os.path.relpath(abspath, rabs)
            if best is None or len(rel) < len(best):
                best = rel
    return (best or norm).replace(os.sep, "/")


def main(argv: list[str]) -> int:
    ap = argparse.ArgumentParser(description="C++ reflection/serialization code generator.")
    ap.add_argument("inputs", nargs="+", help="Header files to scan for COMPONENT/PROPERTY.")
    ap.add_argument("--out", required=True, help="Output .cpp path (a sibling .h is also written).")
    ap.add_argument("-I", "--include", action="append", default=[], dest="includes", help="Add an include search dir (passed to clang). Repeatable.")
    ap.add_argument("--include-root", action="append", default=[], dest="include_roots", help="Strip this prefix when forming #include lines. Repeatable.")
    ap.add_argument("-D", "--define", action="append", default=[], dest="defines", help="Extra preprocessor define. Repeatable.")
    ap.add_argument("--std", default="c++20", help="C++ standard (default: c++20).")
    ap.add_argument("--clang-arg", action="append", default=[], dest="clang_args", help="Raw extra argument forwarded to clang. Repeatable.")
    ap.add_argument("--namespace", default="Source::Serialization", help="Namespace for the generated function.")
    ap.add_argument("--function", default="BindECS", help="Name of the generated registration function.")
    ap.add_argument("--registry-type", default="Source::ECS::Registry", help="Fully-qualified ECS registry type for the function parameter.")
    ap.add_argument("--libclang", help="Path to libclang shared library.")
    ap.add_argument("--werror", action="store_true", help="Treat parse diagnostics as fatal.")
    args = ap.parse_args(argv)

    _load_libclang(args.libclang)
    from clang.cindex import Index, TranslationUnit, Diagnostic

    base_args = ["-x", "c++", f"-std={args.std}", "-DREFLECTION_CODEGEN"]
    base_args += [f"-D{d}" for d in args.defines]
    base_args += [f"-I{p}" for p in args.includes]
    base_args += args.clang_args

    index = Index.create()

    warnings: list[str] = []
    def warn(msg: str):
        warnings.append(msg)
        print(f"reflectgen: warning: {msg}", file=sys.stderr)

    all_components: list[Component] = []
    seen_types: set[str] = set()
    had_fatal = False

    for inp in args.inputs:
        if not os.path.exists(inp):
            sys.exit(f"error: input not found: {inp}")
        tu = index.parse(
            inp, args=base_args,
            options=TranslationUnit.PARSE_SKIP_FUNCTION_BODIES
                    | TranslationUnit.PARSE_INCOMPLETE,
        )
        for d in tu.diagnostics:
            if d.severity >= Diagnostic.Error:
                print(f"reflectgen: clang: {inp}: {d.spelling}", file=sys.stderr)
                if args.werror:
                    had_fatal = True

        inc = make_include_path(inp, args.include_roots)
        for comp in collect_components(tu, inc, warn):
            if comp.qualified_type in seen_types:
                continue
            seen_types.add(comp.qualified_type)
            all_components.append(comp)

    if had_fatal:
        sys.exit("error: clang reported errors and --werror was set")

    all_components.sort(key=lambda c: c.qualified_type)

    header_name = os.path.splitext(os.path.basename(args.out))[0] + ".h"
    hdr_text, src_text = emit(
        all_components,
        namespace=args.namespace,
        function=args.function,
        registry_type=args.registry_type,
        header_name=header_name,
        warnings=warnings,
    )

    out_dir = os.path.dirname(os.path.abspath(args.out))
    os.makedirs(out_dir, exist_ok=True)
    with open(args.out, "w") as f:
        f.write(src_text)
    with open(os.path.join(out_dir, header_name), "w") as f:
        f.write(hdr_text)

    total_fields = sum(len(c.members) for c in all_components)
    print(f"reflectgen: {len(all_components)} component(s), {total_fields} field(s) "
          f"-> {args.out}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))