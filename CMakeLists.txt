cmake_minimum_required(VERSION 3.15)
project(StreetFighterClone LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Allow toggling debug build from CLion
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Options matching your Makefile
option(ENABLE_WARNINGS "Enable compiler warnings" ON)
option(WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
option(OS_WINDOWS "Build on Windows" OFF)

# Collect all source files recursively
file(GLOB_RECURSE CXX_SOURCES
        CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
# Filter out CMake's build files (anything inside the build directory)
list(FILTER CXX_SOURCES EXCLUDE REGEX ".*/CMakeFiles/.*")
list(FILTER CXX_SOURCES EXCLUDE REGEX "${CMAKE_BINARY_DIR}/.*")


# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Create executable
add_executable(${PROJECT_NAME} ${CXX_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
        Assets
        Characters
        GameObjects
        Utils
)

# Compiler flags
if(ENABLE_WARNINGS)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(WARNINGS_AS_ERRORS)
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
endif()

# Debug/Release settings
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build: Adding -g -O0")
    target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME mainDebug)
else()
    message(STATUS "Release build: Adding -O3")
    target_compile_options(${PROJECT_NAME} PRIVATE -O3)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME mainRelease)
endif()

# Link Raylib and system libraries
if(OS_WINDOWS)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib opengl32 gdi32 winmm)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib GL m pthread dl rt X11)
endif()

# Optional: print all collected source files for debugging
message(STATUS "Source files: ${CXX_SOURCES}")

# Add this to your existing CMakeLists.txt
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            VS_DEBUGGER_COMMAND_ARGUMENTS "ulimit -n 1024")
endif()
