#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "Bomberman_Map.hpp"
#include "CreateElement.hpp"
#include "Graphic.hpp"
#include "IElement.hpp"
#include "MyEventReceiver.hpp"
#include "Player_graphic.hpp"
#include "include/irrlicht.h"

class Camera {
public:
  Camera(Graphic *graphic);
  ~Camera() {}
  void SpecMode();
  void GameMode();
  void setGraphic(Graphic *graphic);

private:
  Graphic *_graphic;
};

#endif
