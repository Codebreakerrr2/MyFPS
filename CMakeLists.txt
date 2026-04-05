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

        #------------------
        #Shader src files
        #-----------------------
        src/shader/OpenGLShader.cpp


        #------------------
        #camera src files
        #-----------------------

        src/camera/Camera.cpp
        src/camera/CameraController.cpp

        #------------------
        #Input src files
        #-------------------
        src/input/InputKeyboard.cpp
        src/input/InputMouse.cpp
        src/input/InputXBOX.cpp

        #------------------
        #renderer source files
        #-------------------
        src/renderer/OpenGLRenderer.cpp

        #------------------
        #window src files
        #-------------------
        src/window/GLFWWindow.cpp


        #------------------
        #mesh source files
        #-------------------
        src/mesh/OpenGLMesh.cpp


        #----------------------
        # Logger src files
        #---------------------
        src/profiling/ConsoleLogger.cpp
        src/profiling/FileLogger.cpp
        src/profiling/LoggerManager.cpp
        src/profiling/UILogger.cpp

        #-----------------
        #geometry src files
        #---------------------

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

        #----------------
        #world src files
        #--------------
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
        tests/profilingTests.cpp
        tests/databaseTests.cpp
        #-------------------
        #editor src files
        #------------------

        #------------------
        #assets manager src files
        #-------------------


        src/shader/OpenGLShader.cpp

        src/camera/Camera.cpp


        #------------------
        #renderer source files
        #-------------------
        src/renderer/OpenGLRenderer.cpp

        #------------------
        #window src files
        #-------------------
        src/window/GLFWWindow.cpp


        #------------------
        #mesh source files
        #-------------------
        src/mesh/OpenGLMesh.cpp


        #----------------------
        # Logger src files
        #---------------------
        src/profiling/ConsoleLogger.cpp
        src/profiling/FileLogger.cpp
        src/profiling/LoggerManager.cpp
        src/profiling/UILogger.cpp

        #-----------------
        #geometry src files
        #---------------------

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

        #----------------
        #world src files
        #--------------
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
