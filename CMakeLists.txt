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

#-----------------------
#--GLAD --------------
#-------------------
add_library(glad
    external_libraries/glad.c
)
target_include_directories(glad PUBLIC
        external_libraries/include
)


# -----------------------------
# GLFW
# -----------------------------
include(FetchContent)
FetchContent_Declare(
        glfw
        URL GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG master
)
FetchContent_MakeAvailable(glfw)


#---------------
# win32 Socket
#----------------------


#-------------------
#--ENGINE LIBRARY---
#--------------------

add_library(Engine 

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
        #------------------

        #------------------
        #network src files
        #---------------------
        src/network/UDP.cpp
        src/network/NetworkInit.cpp
        src/network/Client.cpp
        src/network/Server.cpp

        #------------
        #Math src files
        #--------------
        src/Math/Vec.cpp
        src/Math/Mat4.cpp

)
target_include_directories(Engine PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(Engine PUBLIC
        glad
        glfw
        opengl32
        user32
        gdi32
        ws2_32
)



# -----------------------------
# Executable
# -----------------------------

add_executable(Game 
        src/main.cpp
)

target_link_libraries(Game PRIVATE Engine)

# Erzwingt statisches Linking der Laufzeit
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

# -----------------------------
# Copy assets to runtime dir
# -----------------------------
add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
)

add_dependencies(Game copy_assets)

#-------------------------
# Google Test
#-------------------------
add_executable(EngineTests
       tests/databaseTests.cpp 
       tests/profilingTests.cpp
)

target_link_libraries(EngineTests PRIVATE Engine)

include(GoogleTest)
gtest_discover_tests(EngineTests)
