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

# Core game/engine sources (platform-independent)
set(MYFPS_SOURCES
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
        src/game/Player.cpp
        src/game/Enemy.cpp
        src/world/Map.cpp
        src/math/Vec.cpp
        src/math/Mat4.cpp
)

# Networking is currently implemented with WinSock2 and is only
# available on Windows builds.
if (WIN32)
    list(APPEND MYFPS_SOURCES
            src/network/UDP.cpp
            src/network/NetworkInit.cpp
            src/network/Client.cpp
            src/network/Server.cpp
    )
endif ()

add_executable(MyFPS ${MYFPS_SOURCES})

target_include_directories(MyFPS PRIVATE
        include
        ${GLFW_INCLUDE_DIR}
)

if (WIN32)
    target_link_libraries(MyFPS PRIVATE
            glad
            glfw
            opengl32
            user32
            gdi32
            ws2_32
    )
else ()
    # macOS / Linux: use system OpenGL instead of Win32 libs
    find_package(OpenGL REQUIRED)
    target_link_libraries(MyFPS PRIVATE
            glad
            glfw
            OpenGL::GL
    )
endif ()
# -----------------------------
# Copy assets to runtime dir
# -----------------------------
add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
)

add_dependencies(MyFPS copy_assets)
