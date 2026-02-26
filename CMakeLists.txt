cmake_minimum_required(VERSION 3.20)
project(FPS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


#-----------------------
# Google Test
#-------------------
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Für Windows wichtig
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()





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

        #------------------
        #assets manager src files
        #-------------------
        src/asset_manager/EntityManager.cpp
        src/asset_manager/ShaderManager.cpp



        #-----------------
        #geometry src files
        #---------------------
        src/geometry/geometry.cpp

        #------------------
        #network src files
        #---------------------
        src/network/UDP.cpp
        src/network/NetworkInit.cpp
        src/network/Client.cpp
        src/network/Server.cpp

        #-----------------
        #game src files
        #----------------
        src/game/Player.cpp
        src/game/Enemy.cpp
        #----------------
        #world src files
        #--------------
        src/world/Map.cpp
        #------------
        #Math src files
        #--------------
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

#-------------------------
# Google Test
#-------------------------
add_executable(EngineTests
        tests/geometryTest.cpp
        tests/EntityManagerTest.cpp
        tests/ShaderManagerTest.cpp





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

        #------------------
        #assets manager src files
        #-------------------
        src/asset_manager/EntityManager.cpp
        src/asset_manager/ShaderManager.cpp



        #------------------
        #geometry src files
        #---------------------
        src/geometry/geometry.cpp

        #------------------
        #network src files
        #---------------------
        src/network/UDP.cpp
        src/network/NetworkInit.cpp
        src/network/Client.cpp
        src/network/Server.cpp

        #-----------------
        #game src files
        #----------------
        src/game/Player.cpp
        src/game/Enemy.cpp
        #----------------
        #world src files
        #--------------
        src/world/Map.cpp
        #------------
        #Math src files
        #--------------
        src/Math/Vec.cpp
        src/Math/Mat4.cpp


)

target_link_libraries(EngineTests
        gtest_main
        glad
        glfw
        opengl32
        user32
        gdi32
        ws2_32

)

target_include_directories(EngineTests PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

include(GoogleTest)
gtest_discover_tests(EngineTests)
