cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(gbFighter)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()
# find the nlohmann_json package which was installed with vcpkg
find_package(nlohmann_json CONFIG REQUIRED)


# Our Project
add_executable(${PROJECT_NAME} main.cpp
        GameObjects/BaseSpriteObject.cpp
        GameObjects/BaseSpriteObject.h
        Characters/BaseCharacter.cpp
        Characters/BaseCharacter.h
        Utils/AsepriteManager.cpp
        Utils/AsepriteManager.h
        Characters/Fighter_Andi.cpp
        Characters/Fighter_Andi.h
        Constants.h
        Constants.cpp
        Utils/Screen2DManager.cpp
        Utils/Screen2DManager.h
        GameObjects/CollisionBox2D.cpp
        GameObjects/CollisionBox2D.h
        GameObjects/BaseGameObject.cpp
        GameObjects/BaseGameObject.h
)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib nlohmann_json::nlohmann_json)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

