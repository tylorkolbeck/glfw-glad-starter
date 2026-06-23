cmake_minimum_required(VERSION 3.10)
project(OpenGLWindow CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find GLFW3 via pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

# -------------------------------------------------------------
# AUTOMATED SOURCE DISCOVERY
# -------------------------------------------------------------
# Automatically gather all source and header files from src/
file(GLOB_RECURSE ENGINESOURCES 
    "src/*.cpp" 
    "src/*.h" 
    "src/*.hpp"
)

# Hand-map static vendor dependencies that don't change
set(VENDOR_SOURCES
    vendor/glad/src/glad.c
)

# Combine them into the final build target executable
add_executable(${PROJECT_NAME} ${ENGINESOURCES} ${VENDOR_SOURCES})

# -------------------------------------------------------------
# INCLUDE DIRECTORIES & LINK LIBRARIES
# -------------------------------------------------------------
# Target-specific include options (Tells the compiler where to find headers)
target_include_directories(${PROJECT_NAME} PRIVATE 
    src
    vendor/glad/include
    ${GLFW_INCLUDE_DIRS}
)

# Target-specific linker options (Tells the linker where to map compiled symbols)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${GLFW_LIBRARIES} 
    ${CMAKE_DL_LIBS}
)
