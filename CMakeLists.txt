cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(project_name OpenGL-game)
project(${project_name})

add_executable(${project_name} 
	src/main.cpp
	src/Renderer/ShaderProgram.cpp
	src/Renderer/ShaderProgram.h
	src/Resources/ResourceManager.cpp
	src/Resources/ResourceManager.h
	)

target_compile_features(${project_name} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${project_name} glfw)

add_subdirectory(external/glad)
target_link_libraries(${project_name} glad)

set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${project_name} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${project_name}>/res)