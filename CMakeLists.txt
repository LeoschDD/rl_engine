cmake_minimum_required(VERSION 4.0)
project(rl_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external/raylib)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(imgui)
include(rlimgui)
add_subdirectory(external/JoltPhysics/Build)
add_subdirectory(external/box2d)

add_subdirectory(engine)
add_subdirectory(application)