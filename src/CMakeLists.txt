cmake_minimum_required(VERSION 2.8)

project("Game" CXX)

include(GNUInstallDirs)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../modules")

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1 sfml-audio>=2.1)
find_package(Boost REQUIRED COMPONENTS filesystem system)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/local/config.h.in ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/local/config.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY})

add_definitions(-Wall -g -O2 -std=c++11)

add_executable(Game
  # Julien Bernard Gameskel (https://github.com/jube/gameskel)
  # base
  game/AssetManager.cc
  game/Clock.cc
  game/EventManager.cc
  game/Log.cc
  game/Random.cc
  # graphics
  game/Action.cc
  game/Animation.cc
  game/Camera.cc
  game/Control.cc
  game/Entity.cc
  game/EntityManager.cc
  game/ResourceManager.cc
  game/WindowGeometry.cc
  game/WindowSettings.cc
  # model
  game/Model.cc
  game/ModelManager.cc
  #perlin
  local/Noise.cc
  local/Heightmap.cc
  local/Tilemap.cc
  local/Character.cc
  local/Obstaclemap.cc
  #game
  Game.cpp
)

target_link_libraries(Game
	${SFML2_LIBRARIES}
	${Boost_LIBRARIES}
)
