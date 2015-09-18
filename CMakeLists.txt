#################
# DO NOT DELETE #
#################

# This exists because CLion needs it
# to know how to build the project.

cmake_minimum_required(VERSION 3.3)

project(game-client)
add_executable(game-client Main.cpp GameController.cpp GameController.h UDPClient.cpp)

add_subdirectory(include/rapidjson-master)