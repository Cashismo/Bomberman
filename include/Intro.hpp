#ifndef __INTRO_HPP__
#define __INTRO_HPP__

#include "Graphic.hpp"
#include "include/irrKlang.h"
#include "include/irrlicht.h"
#include <chrono>
#include <thread>

class Intro {
public:
  Intro(Graphic *graphic);
  ~Intro();
  void play();

private:
  Graphic *_graphic;
  irr::scene::ISceneNode *player;
  irr::scene::ISceneNode *bomb;
};

#endif
