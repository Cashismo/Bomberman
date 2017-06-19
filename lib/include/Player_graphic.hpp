#ifndef PLAYER_GRAPHIC_HPP
# define PLAYER_GRAPHIC_HPP

#include <string>
#include <iostream>
#include "include/irrlicht.h"
#include "Graphic.hpp"

class Player_graphic
{
  irr::IrrlichtDevice *device;
  irr::scene::ISceneNode *player;
  bool init;
public :
  Player_graphic();
  void setPos(float X, float Y);
  void setDevice(irr::IrrlichtDevice *_device) { device = _device; }
};

# endif
