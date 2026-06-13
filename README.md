> [!WARNING]
> **🚧 Heavily work in progress.** Odyssey Engine is in early, active development.

# Odyssey Engine

A custom 3D game engine in C++23 with a separate C#/WPF editor. The editor communicates with the engine over a local socket, allowing the engine to be restarted independently if it crashes without taking down the editor.

---

## Overview

![Overview](Assets/Overview.png)

### Engine (C++23)

A standalone runtime that owns the window, the renderer, and the world.

- **Rendering** - OpenGL 4.6 core profile via GLAD, windowing through GLFW, math via GLM. A simple forward renderer draws meshes with a per-object model matrix and flat color.
- **ECS** - a sparse-set entity-component registry. Entities are an index + version pair; components live in packed pools for cache-friendly iteration. The registry exposes `Create`, `Destroy`, `Add`, `Remove`, `Has`, `Get`, and a templated `View<...>` for system queries.
- **Components & systems** - `Transform`, `MeshRenderer`, and `Spin` components, driven by a `RenderSystem` and a `SpinSystem`. Systems iterate the world each frame through the registry's view API.
- **Messaging** - a thread-safe `EventBus` supporting immediate publish, deferred enqueue/flush, prioritized handlers, and scoped subscriptions.
- **Editor bridge** - a TCP server that speaks a small RPC + event protocol. Requests carry an `id`, `method`, and `params`; the engine answers with typed JSON. Outbound and inbound event types are registered through a `JsonProxy` so payloads serialize automatically.

### Editor (C#, .NET 10)

A native WPF desktop application built on a clean, layered architecture.

- **Domain / Application / UI** - strict separation of concerns. The Application layer holds framework-agnostic services and interfaces; the UI layer is WPF + MVVM.
- **MVVM** - view models built on `CommunityToolkit.Mvvm`, wired together with `Microsoft.Extensions.Hosting` dependency injection.
- **Panels** - a Hierarchy, an Inspector, a Console, a Controls bar, and a Workspace that hosts the embedded engine.
- **Services** - a logging service with leveled output piped to the in-editor console, and an undo/redo service backed by a command stack.
- **Engine connection** - an async TCP client with length-prefixed JSON framing, request/response correlation via `TaskCompletionSource`, background read loop, and connection retry.

### How the embedding works

When the workspace opens, the editor:

1. Launches the engine process headless (`-hide`) on a chosen port.
2. Connects to the engine's socket and retries until the runtime is listening.
3. Sends a `get_viewport` request and receives the engine window's native handle (HWND).
4. Reparents that window into a WPF `HwndHost`, restyles it as a child window, and keeps it sized to the panel.

The result is a single editor window with the real, live C++ OpenGL viewport rendering inside it.

---

## Tech stack

| Area | Choice |
|------|--------|
| Engine language | C++23 |
| Graphics | OpenGL 4.6 core, GLAD, GLFW, GLM |
| Serialization | nlohmann/json |
| Engine build | CMake + Ninja, MSVC 2022 |
| Editor language | C# / .NET 10 |
| Editor UI | WPF, MVVM (CommunityToolkit.Mvvm) |
| DI / hosting | Microsoft.Extensions.Hosting |
| Engine ↔ editor | TCP, length-prefixed JSON (RPC + events) |
| Task runner | `just` |

---

## Prerequisites

> Windows-only - the editor uses WPF and native HWND reparenting, and the engine builds with MSVC.

- Visual Studio 2022 **Build Tools** (MSVC toolchain)
- [Ninja](https://ninja-build.org/) - `winget install Ninja-build.Ninja`
- [just](https://github.com/casey/just) - `winget install Casey.Just`
- .NET 10 SDK (for the editor)
- Python 3 with `libclang` (for the reflection code generator) - `pip install libclang`

CMake fetches GLFW, GLAD, GLM, and nlohmann/json automatically on first configure.

## Setup

Set the path to your `VsDevCmd.bat` in `justconfig.json`.

## Build & run

Build the engine:

```sh
just build-engine
```

Clean engine build artifacts:

```sh
just clean-engine
```

Build the editor:

```sh
just build-editor
```

Run the editor:

```sh
just run-editor
```

Then run the editor from your .NET tooling. It will launch the engine, connect, and embed the viewport.

The engine can also run standalone via the launcher, which accepts:

| Flag | Effect |
|------|--------|
| `-game` / `-editor` | launch mode |
| `-hide` | run without showing its own window (used when embedded) |
| `-port <n>` | editor bridge port |
| `-width` / `-height <n>` | window size |
| `-vsync <0\|1>` | toggle vsync |
