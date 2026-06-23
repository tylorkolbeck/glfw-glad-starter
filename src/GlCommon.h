#ifndef GL_COMMON_H
#define GL_COMMON_H

// 1. Tell GLFW not to include the legacy system OpenGL headers
#define GLFW_INCLUDE_NONE

// 2. Turn off GLAD header-only definitions to prevent linker collisions
#define GLAD_GL_NO_HEADER_ONLY

// 3. Include the actual OpenGL/Windowing library components
// Note: Some setups use <glad/gl.h>, others use <glad/glad.h>.
// Match this to whatever header file name your GLAD generation outputted.
#include <GLFW/glfw3.h> // IWYU pragma: export
#include <glad/glad.h>  // IWYU pragma: export

#endif // GL_COMMON_H
