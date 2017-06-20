#ifndef PLAYER_GRAPHIC_HPP
# define PLAYER_GRAPHIC_HPP

#include <string>
#include <iostream>
#include "include/irrlicht.h"
#include "Graphic.hpp"

class Graphic;

class Player_graphic
{
  irr::IrrlichtDevice *device;
  irr::scene::ICameraSceneNode *camera;  //  irr::scene::ISceneNode *player;
  irr::scene::IAnimatedMeshSceneNode *player;
  Graphic *graphic;
  bool init;
  int place;
  int type;
  int x;
  int y;
  int direction;
public :
  Player_graphic(Graphic *graphic, int _place, int _type);
  void setPos(float X, float Y);
  void setDevice(irr::IrrlichtDevice *_device) { device = _device; }
  void die();
  void rotate(int dir);
  void setLife(int);
  void setBomb(int bomb);
  void setSpeed(int nb);
};

# endif
