# 🛠️ OpenGL & CMake Workflow Cheat Sheet

This reference guide outlines the exact commands and steps required when modifying the structure of your C++ graphics project.

---

## 1. Adding a New Source or Header File (`.cpp`, `.h`)

When you create a new file (for example, `src/Shader.cpp` or `src/Shader.h`), CMake doesn't know it exists until you explicitly add it to the compilation target.

1. **Update `CMakeLists.txt`**
   Append the new file path to your `SOURCES` variable array:

   ```cmake
   set(SOURCES
       src/main.cpp
       src/GLCommon.h
       src/Shader.h    # <-- Add new header files here
       src/Shader.cpp  # <-- Add new implementation files here
       third_party/glad/src/gl.c
   )
   Regenerate & Link Tracking
   Run this unified command chain in your terminal. This forces CMake to re-index the project tree and updates the compile_commands.json database file so Neovim (clangd) can map out the symbols correctly:
   ```

Bash
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON && ln -sf build/compile_commands.json .
Refresh Neovim LSP
Inside your active editing buffer, tell your language server provider to reload the tracking map so your screen diagnostics instantly clear:

Vim Script
:LspRestart 2. Adding a New Third-Party System Library
If you install a dependency globally on your machine (like adding the linear algebra library glm or an audio library via apt), update your project's configuration file:

Update CMakeLists.txt
Use pkg-config or CMake's native find_package to locate the files, and append the libraries to your linker target:

CMake

# 1. Locate the package

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLM REQUIRED glm) # Example package lookup

# 2. Link it to your executable target

target_link_libraries(${PROJECT_NAME} PRIVATE ${GLFW_LIBRARIES} ${GLM_LIBRARIES} ${CMAKE_DL_LIBS})
Regenerate & Link Tracking

Bash
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON && ln -sf build/compile_commands.json .
Refresh Neovim LSP

Vim Script
:LspRestart 3. Modifying Existing Code Only
If you are just editing rendering math or rewriting logic inside files that are already tracked by CMake:

Compile the changes:

Bash
cmake --build build
Run the compiled application binary:

Bash
./build/OpenGLWindow
Note: Standard text modifications inside your source files do not require re-running your base cmake -B configuration line or restarting your Neovim LSP!

1. Core Development Rules to Keep in Mind
   Include Order Priority
   Graphics rendering relies strictly on correct compilation ordering. GLAD definitions must load completely before GLFW window operations are called. Always ensure your centralized configuration block is placed at the absolute top of your files.

Formatter Controls
If your auto-formatting setups inside Neovim (conform.nvim / clang-format) aggressively rearrange your imports on save, explicitly lock down your configuration includes with comments:

C++
// clang-format off
# include "GLCommon.h"
// clang-format on

# include <iostream>
IWYU Headers (Include What You Use)
To cleanly aggregate all graphics library requirements within a unified hub header while preventing clangd from generating unused import warnings inside files like main.cpp, tag your internal library references with explicit export signals:

C++
# ifndef GL_COMMON_H
# define GL_COMMON_H

# define GLFW_INCLUDE_NONE
# define GLAD_GL_NO_HEADER_ONLY

# include <glad/gl.h> // IWYU pragma: export
# include <GLFW/glfw3.h> // IWYU pragma: export

# endif // GL_COMMON_H
