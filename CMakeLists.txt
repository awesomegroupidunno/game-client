cmake_minimum_required(VERSION 3.0.2)
project(game-client)

add_executable(game-client Main.cpp GameController.cpp GameController.h include/SDLutil.h GameState.cpp Vehicle.cpp Vehicle.h SdlGameView.cpp SdlGameViewAdapter.cpp SdlGameViewAdapter.h client/UdpClient.cpp client/UdpClient.h client/EncodeDecode.h client/JsonEncodeDecode.cpp client/JsonEncodeDecode.h client/NetworkClient.h client/Listener.cpp client/Listener.h SdlInputAdapter.cpp SdlInputAdapter.h SdlGameView.h client/Command.h GameState.h Base.cpp Base.h)

# Add header files
include_directories(include client)

# Add to modules list
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${game-client_SOURCE_DIR}/include/cmake")

# Set vars
set(BUILD_DIR "${game-client_SOURCE_DIR}/build/")

# Link to SDL
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(game-client ${SDL2_LIBRARY})

# Link to OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(game-client ${OPENGL_LIBRARIES})

# Link to GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})
target_link_libraries(game-client ${GLEW_LIBRARIES})

# Link to RapidJSON
find_package(RapidJSON)
include_directories(${RapidJSON_INCLUDE_DIR})
target_link_libraries(game-client ${RapidJSON_LIBRARY})
