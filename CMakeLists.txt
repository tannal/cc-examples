cmake_minimum_required(VERSION 3.0.0)
project(ray VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

file(GLOB EXAMPLE_SOURCES "*.c" "*.cc")

find_package(raylib 3.0 REQUIRED)


foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)

    if(${EXAMPLE_NAME} MATCHES "multithread_bank" AND WIN32)
        continue()
    endif()
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})

    if(${EXAMPLE_SOURCE} MATCHES "Sierpinski.cc")
        set(CMAKE_CXX_STANDARD 17)
        set(CMAKE_CXX_STANDARD_REQUIRED ON)
        set(CMAKE_CXX_EXTENSIONS OFF)
        target_link_libraries(${EXAMPLE_NAME} PRIVATE raylib)
    endif()

    
endforeach()