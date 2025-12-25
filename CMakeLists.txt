cmake_minimum_required(VERSION 3.20)
project(FPS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# -----------------------------
# GLFW
# -----------------------------
set(GLFW_ROOT "${CMAKE_SOURCE_DIR}/glfw")
set(GLFW_INCLUDE_DIR "${GLFW_ROOT}/include")
set(GLFW_LIB_FILE "${GLFW_ROOT}/lib-mingw-w64/libglfw3.a")

# -----------------------------
# GLAD
# -----------------------------
add_library(glad STATIC
        src/glad.c
)

target_include_directories(glad PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

# -----------------------------
# Executable
# -----------------------------
add_executable(MyFPS
        src/main.cpp
        src/engine/Renderer.cpp
        src/engine/Input.cpp
        src/engine/Physics.cpp
        src/engine/Shader.cpp
        src/engine/Mesh.cpp
        src/engine/Camera.cpp
        src/engine/Entity.cpp
        src/engine/parser.cpp
        src/game/Player.cpp
        src/game/Enemy.cpp
        src/world/Map.cpp
        src/Math/Vec.cpp
        src/Math/Mat4.cpp


)

target_include_directories(MyFPS PRIVATE
        include
        ${GLFW_INCLUDE_DIR}
)

target_link_libraries(MyFPS PRIVATE
        glad
        ${GLFW_LIB_FILE}
        opengl32
        user32
        gdi32
)
