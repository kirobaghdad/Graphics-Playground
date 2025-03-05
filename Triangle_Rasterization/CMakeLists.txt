set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe" )
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe" )
cmake_minimum_required(VERSION 3.31.5)
project(myproject VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)        # Don't build Documentation
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)       # Don't build Tests
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)    # Don't build Examples
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)           # Don't build Installation Information
set(GLFW_USE_HYBRID_HPG ON CACHE BOOL "" FORCE)     # Add variables to use High Performance Graphics Card if available

add_subdirectory(vendor/glfw)

include_directories(
    vendor/glfw/include
    vendor/glad/include
    vendor/glm
    include
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)

add_executable(myprogram
    main.cpp
    vendor/glad/src/gl.c
    src/triangle_rasterization.cpp
)    

target_link_libraries(myprogram PRIVATE glfw)
