cmake_minimum_required(VERSION 3.5)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3 -lpthread -g3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

project(indie_studio)

add_executable(
  indie_studio
  main.cpp
  sources/player/Player.cpp
  sources/player/AI.cpp
  sources/bonus/Bonus.cpp
  sources/bomb/Bomb.cpp
  sources/obstacle/Obstacle.cpp
  sources/create_elements/CreateElement.cpp
  sources/bomberman/Bomberman.cpp
  sources/menu/ConfFile.cpp
  sources/menu/Menu.cpp
  sources/camera/Camera.cpp
  sources/intro/Intro.cpp
  sources/Saves.cpp
  Bomberman_Map.cpp
  irrlicht/Graphic.cpp
  irrlicht/Object.cpp
  irrlicht/Player_graphic.cpp
  sources/randmap/Randmap.cpp
)

TARGET_LINK_LIBRARIES(indie_studio "/usr/local/lib/libIrrlicht.so")
TARGET_LINK_LIBRARIES(indie_studio "/usr/local/lib/libIrrKlang.so")
