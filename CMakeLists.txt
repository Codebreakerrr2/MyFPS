cmake_minimum_required(VERSION 3.20)
project(FPS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# -----------------------------
# GLFW
# -----------------------------
add_subdirectory(glfw)

# -----------------------------
# GLAD
# -----------------------------
add_library(glad STATIC
        src/glad.c
)

target_include_directories(glad PUBLIC
        ${CMAKE_SOURCE_DIR}/include

)
#---------------
# win32 Socket
#----------------------


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
        src/engine/CameraController.cpp
        src/engine/CameraFollower.cpp

        #-------------------
        #editor src files
        #------------------
        src/editor/Editor.cpp
        src/editor/Gizmos.cpp


        src/geometry/geometry.cpp
        src/network/UDP.cpp
        src/network/NetworkInit.cpp
        src/network/Client.cpp
        src/network/Server.cpp
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
        glfw
        opengl32
        user32
        gdi32
        ws2_32
)
# -----------------------------
# Copy assets to runtime dir
# -----------------------------
add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
)

add_dependencies(MyFPS copy_assets)
