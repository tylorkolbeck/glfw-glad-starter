# 🚀 Modern OpenGL C++ Starter Template

A clean, high-performance starter template for modern OpenGL graphics programming utilizing **C++20**, **GLFW**, **GLAD**, and **CMake**.

This repository features automated file tracking (globbing) and a streamlined `Makefile` automation layer optimized for **Neovim** development environments with `clangd`.

---

## 🏗️ Project Architecture

The workspace segregates core game/engine logic from local static vendor dependencies:

```text
├── CMakeLists.txt         # Project build logic
├── Makefile               # Shortcut workflow automation
├── src/                   # Core application source tree
│   ├── GlCommon.h         # Unified graphics configurations & wrapper
│   └── main.cpp           # App context and main loop entry
└── vendor/                # Vendored dependencies
    └── glad/
        ├── include/       # GLAD tracking headers
        └── src/
            └── glad.c     # Generated GLAD source mapping
```

---

## 📋 Prerequisites

Ensure your system has a C++20 compiler, CMake, and the native windowing/display development headers installed.

### Ubuntu / Debian / WSL

```bash
sudo apt update
sudo apt install build-essential cmake pkg-config libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev libglfw3-dev
```

### Arch Linux

```bash
sudo pacman -S base-devel cmake pkgconf glfw-wayland # or glfw-x11 depending on backend
```

---

## 🚀 Quick Start / Setup

When cloning this repository or initializing a new project instance from it, follow these three steps to build, map, and run:

### 1. Synchronize Project & IDE Tracking

Generate the local CMake build files and map out symbols for your Neovim Language Server Protocol (`clangd`):

```bash
make sync
```

_If you are already inside a Neovim buffer, run `:LspRestart` to instantly sync tracking metrics._

### 2. Compile and Build

Compile the application executable binaries using the local cache:

```bash
make build
```

### 3. Run the Target Window

Execute the built context to display the default dark blue viewport:

```bash
make run
```

> 💡 **Pro-Tip:** You can combine compilation and execution into a single inline action using:
>
> ```bash
> make && make run
> ```

---

## 🛠️ Daily Development Workflow

Thanks to CMake automated discovery features, you **do not** need to manually add files to your build configurations when scaling your engine.

### Adding a New File (`.cpp`, `.h`, `.hpp`)

1. Simply create the file inside the `src/` directory (e.g., `src/Shader.cpp`).
2. Run `make sync` in your terminal to allow the automatic discovery process to register it.
3. Reload your buffer environment to ensure clean diagnostics.

### Resetting the Project Cache

If structural dependencies change drastically or you notice configuration mismatches, completely wipe out local build artifacts and start fresh:

```bash
make clean
```

---

## 📝 Core Rules & Configurations

### Include Order Priority

Graphics rendering relies strictly on correct compilation ordering. **GLAD definitions must load completely before GLFW window operations are called.** Always ensure your centralized configuration block is placed at the absolute top of your files.

### Formatter Controls

If your auto-formatting setups inside Neovim (`conform.nvim` / `clang-format`) aggressively rearrange your imports on save, explicitly lock down your configuration includes with comments:

```cpp
// clang-format off
#include "GlCommon.h"
// clang-format on

#include <iostream>
```

### IWYU Headers (Include What You Use)

To cleanly aggregate all graphics library requirements within a unified hub header while preventing `clangd` from generating unused import warnings inside files like `main.cpp`, tag your internal library references with explicit export signals inside `src/GlCommon.h`:

```cpp
#ifndef GL_COMMON_H
#define GL_COMMON_H

#define GLFW_INCLUDE_NONE
#define GLAD_GL_NO_HEADER_ONLY

#include <glad/glad.h>   // IWYU pragma: export
#include <GLFW/glfw3.h> // IWYU pragma: export

#endif // GL_COMMON_H
```

```

```
