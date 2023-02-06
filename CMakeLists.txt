cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(cdecl LANGUAGES C)

# Binaries will be under 'bin' directory.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCES
    src/acl_stack.c
    src/main.c)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

if (UNIX)
    # Compiling under Cygwin, Linux
    # Assumes GCC
    target_compile_options(${PROJECT_NAME}
                           PRIVATE
                           -Wall
                           -Wextra
                           -std=c99
                           -Wpedantic
                           -Werror)
elseif(WIN32)
    # Compiling under Win32 and Win64
    # Assumes Microsoft Visual C++
    target_compile_options(${PROJECT_NAME}
                           PRIVATE
                           /TP)
endif()
