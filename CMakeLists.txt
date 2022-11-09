cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(project_name OpenGL-game)
project(${project_name})

add_executable(${project_name} src/main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${project_name} glfw)

add_subdirectory(external/glad)
target_link_libraries(${project_name} glad)