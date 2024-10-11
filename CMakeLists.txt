cmake_minimum_required(VERSION 3.10)
project(render_3d)

add_executable(render_3d main.cpp
                Camera/Camera.cpp
                Camera/Camera.h
                Mesh/Mesh.cpp
                Mesh/Mesh.h
                Shader/Shader.cpp
                Shader/Shader.h
                Renderer/Renderer.cpp
                Renderer/Renderer.h)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glfw/lib/libglfw3.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glfw/include"
)

add_library(glew STATIC IMPORTED)
set_target_properties(glew PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glew/lib/glew32s.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glew/include"
)

add_library(freeglut STATIC IMPORTED)
set_target_properties(freeglut PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/freeglut/lib/libfreeglut_static.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/freeglut/include"
)

find_package(OpenGL REQUIRED)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glm")

target_compile_definitions(render_3d PRIVATE FREEGLUT_STATIC GLEW_STATIC)

target_link_libraries(render_3d glfw glew freeglut OpenGL::GL winmm -static)