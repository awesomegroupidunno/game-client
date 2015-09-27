cmake_minimum_required(VERSION 3.0.2)
project(game-client)

add_executable(game-client Main.cpp GameController.cpp GameController.h include/SDLutil.h GameState.cpp Vehicle.cpp Vehicle.h SdlGameView.cpp GameState.cpp SdlGameViewAdapter.cpp SdlGameViewAdapter.h)

# Add header files
include_directories(include)

# Add to modules list
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${game-client_SOURCE_DIR}/include/cmake")

# Set vars
set(BUILD_DIR "${game-client_SOURCE_DIR}/build/")

# Link to SDL
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(game-client ${SDL2_LIBRARY})

# Install
install(TARGETS game-client RUNTIME DESTINATION ${BUILD_DIR})
