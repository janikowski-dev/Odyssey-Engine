from __future__ import annotations

import argparse
import os
import re
import sys
from dataclasses import dataclass
from typing import Optional, List


def _load_libclang(explicit: Optional[str]) -> None:
    from clang import cindex

    candidates = []

    if explicit:
        candidates.append(explicit)

    if os.environ.get("REFLECTGEN_LIBCLANG"):
        candidates.append(os.environ["REFLECTGEN_LIBCLANG"])

    try:
        import clang as _clang_pkg
        bundled = os.path.join(
            os.path.dirname(_clang_pkg.__file__),
            "native",
            "libclang.so"
        )
        candidates.append(bundled)
    except Exception:
        pass

    candidates += [
        "/usr/lib/llvm-19/lib/libclang.so",
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
            "error: could not locate usable libclang. "
            "Use --libclang or set REFLECTGEN_LIBCLANG\n"
            f"{exc}"
        )


@dataclass
class Module:
    name: str
    qualified: str
    include: str


def _annotations(cursor) -> list[str]:
    from clang.cindex import CursorKind
    return [
        c.spelling for c in cursor.get_children()
        if c.kind == CursorKind.ANNOTATE_ATTR
    ]


def _qualified_name(cursor) -> str:
    from clang.cindex import CursorKind

    parts = []
    cur = cursor

    while cur is not None and cur.kind != CursorKind.TRANSLATION_UNIT:
        if cur.spelling:
            parts.append(cur.spelling)
        cur = cur.semantic_parent

    return "::".join(reversed(parts))


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


def collect_modules(tu, include: str, warn) -> list[Module]:
    from clang.cindex import CursorKind

    modules: list[Module] = []

    def visit(cursor):
        for child in cursor.get_children():

            if child.kind in (CursorKind.CLASS_DECL, CursorKind.STRUCT_DECL):
                if child.is_definition():

                    ann = _annotations(child)
                    if any(a.strip().lower().startswith("external_module") for a in ann):

                        if not child.spelling:
                            warn("anonymous MODULE skipped")
                        else:
                            modules.append(Module(
                                name=child.spelling,
                                qualified=_qualified_name(child),
                                include=include
                            ))

            if child.kind in (
                CursorKind.NAMESPACE,
                CursorKind.CLASS_DECL,
                CursorKind.STRUCT_DECL,
                CursorKind.TRANSLATION_UNIT,
                CursorKind.UNEXPOSED_DECL,
            ):
                visit(child)

    visit(tu.cursor)
    return modules


def emit(modules: list[Module], header_name: str):
    guard = re.sub(r"\W", "_", header_name).upper() + "_"

    hdr = [
        f"#ifndef {guard}",
        f"#define {guard}",
        "",
        "#include \"Core/IModuleRegistrar.h\"",
        "",
        "namespace Source::Core",
        "{",
        "    void CreateExternalModules(IModuleRegistrar* Registrar);",
        "}",
        "",
        f"#endif // {guard}",
        ""
    ]

    src = [
        f'#include "{header_name}"',
        "",
    ]

    includes = sorted({m.include for m in modules})
    for inc in includes:
        src.append(f'#include "{inc}"')

    if len(includes) > 0:
        src.append("")

    src += [
        "namespace Source::Core",
        "{",
        "    void CreateExternalModules(IModuleRegistrar* Registrar)",
        "    {",
    ]

    for m in modules:
        src.append(
            f"        Registrar->RegisterModule(MakeUnique<{m.qualified}>());"
        )

    src += [
        "    }",
        "}",
        ""
    ]

    return "\n".join(hdr), "\n".join(src)


def main(argv):
    ap = argparse.ArgumentParser()

    ap.add_argument("inputs", nargs="+")
    ap.add_argument("--out", required=True)

    ap.add_argument("--std", default="c++20")
    ap.add_argument("-I", "--include", action="append", default=[], dest="includes")
    ap.add_argument("-D", "--define", action="append", default=[], dest="defines")
    ap.add_argument("--clang-arg", action="append", default=[], dest="clang_args")

    ap.add_argument("--include-root", action="append", default=[])
    ap.add_argument("--libclang")

    args = ap.parse_args(argv)

    _load_libclang(args.libclang)

    from clang.cindex import Index, TranslationUnit

    index = Index.create()

    def warn(msg):
        print("reflectgen(modules):", msg, file=sys.stderr)

    base_args = [
        "-x", "c++",
        f"-std={args.std}",
        "-DREFLECTION_CODEGEN",
    ]

    base_args += [f"-D{d}" for d in args.defines]
    base_args += [f"-I{p}" for p in args.includes]
    base_args += args.clang_args

    all_modules: list[Module] = []

    for inp in args.inputs:
        if not os.path.exists(inp):
            sys.exit(f"error: missing input: {inp}")

        tu = index.parse(
            inp,
            args=base_args,
            options=TranslationUnit.PARSE_SKIP_FUNCTION_BODIES |
                    TranslationUnit.PARSE_INCOMPLETE
        )

        inc = make_include_path(inp, args.include_root)
        all_modules.extend(collect_modules(tu, inc, warn))

    header_name = os.path.splitext(os.path.basename(args.out))[0] + ".h"

    hdr, src = emit(all_modules, header_name)

    os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)

    with open(args.out, "w") as f:
        f.write(src)

    with open(os.path.join(os.path.dirname(args.out), header_name), "w") as f:
        f.write(hdr)

    print(
        f"modules: {len(all_modules)} module(s) -> {args.out}",
        file=sys.stderr
    )

    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))