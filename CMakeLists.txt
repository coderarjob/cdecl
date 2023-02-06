cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(cdecl LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCES
    acl_stack.c
    main.c)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})
target_compile_options(${PROJECT_NAME}
                       PRIVATE
                       -Wall
                       -std=c99)
