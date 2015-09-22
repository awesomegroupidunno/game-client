cmake_minimum_required(VERSION 3.3)
project(game-client)

add_executable(game-client Main.cpp GameController.cpp GameController.h)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${game-client_SOURCE_DIR}/include/cmake")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(game-client ${SDL2_LIBRARY})