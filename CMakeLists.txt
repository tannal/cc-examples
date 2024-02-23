cmake_minimum_required(VERSION 3.0.0)
project(ray VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

file(GLOB EXAMPLE_SOURCES "*.c" "*.cc")

find_package(raylib 3.0 REQUIRED)
find_package(skia CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)

foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)

    if(${EXAMPLE_NAME} MATCHES "multithread_bank" AND WIN32)
        continue()
    endif()
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})

    # add Carpet.cc to the list of examples that require C++17
    if(${EXAMPLE_SOURCE} MATCHES "Sierpinski.cc|Carpet.cc|drop.cc")
        set(CMAKE_CXX_STANDARD 17)
        set(CMAKE_CXX_STANDARD_REQUIRED ON)
        set(CMAKE_CXX_EXTENSIONS OFF)
        target_link_libraries(${EXAMPLE_NAME} PRIVATE raylib)
    endif()

    if(${EXAMPLE_SOURCE} MATCHES "mandelbrot.cc|mandelbrot_glfw3.cc|mandelbrot_opengl.cc")
        set(CMAKE_CXX_STANDARD 17)
        set(CMAKE_CXX_STANDARD_REQUIRED ON)
        set(CMAKE_CXX_EXTENSIONS OFF)
        target_link_libraries(${EXAMPLE_NAME} PRIVATE skia::skia)
        target_link_libraries(${EXAMPLE_NAME} PRIVATE glfw)
        target_link_libraries(${EXAMPLE_NAME} PRIVATE GLEW::GLEW)
    endif()

    
endforeach()