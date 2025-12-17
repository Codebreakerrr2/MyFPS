cmake_minimum_required(VERSION 3.20)
project(FPS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)



# Engine DLL
add_library(engine SHARED

    src/engine/Renderer.cpp
    src/engine/Input.cpp
    src/engine/Physics.cpp
)

target_include_directories(engine PRIVATE include)


# Game DLL
add_library(game SHARED
    src/game/Player.cpp
    src/game/Enemy.cpp
)

target_include_directories(game PRIVATE include)

# World as DLL
add_library(world SHARED 
src/world/Map.cpp
)
target_include_directories(world PRIVATE include)


# Main executable
add_executable(MyFPS src/main.cpp)
target_link_libraries(MyFPS PRIVATE engine game world)
target_include_directories(MyFPS PRIVATE include)