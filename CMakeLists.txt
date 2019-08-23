cmake_minimum_required(VERSION 3.15)
project(YahahaEngine)

set(CMAKE_CXX_STANDARD_LIBRARIES -lopengl32)

option(GAME_NAME "the name of the game" game)
option(DEBUG "debug mode" OFF)

if(NOT GAME_NAME)
	set(GAME_NAME Yahaha)
endif(GAME_NAME)

if(DEBUG)
	add_compile_definitions(DEBUG)
endif(DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(source)