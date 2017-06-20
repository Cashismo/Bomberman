#ifndef GRAPHIC_HPP_
#define GRAPHIC_HPP_

#include "../include/Bomberman_Map.hpp"
#include "MyEventReceiver.hpp"
#include "Player_graphic.hpp"
#include "include/irrlicht.h"
#include <iostream>
#include <string>
#include <vector>

#include "../irrlicht/Object.hpp"
class Graphic {
  irr::IrrlichtDevice *device;
  irr::video::IVideoDriver *driver;
  irr::scene::ISceneManager *smgr;
  MyEventReceiver receiver;
  irr::scene::ISceneNode *n;
  Bomberman_Map *map;

  std::vector<std::vector<Object *>> objects;
  void display_first();
  std::vector<Object *> create_column(int id);
  void init_objects();

public:
  Graphic(Bomberman_Map *);
  ~Graphic() { device->drop(); }
  void run();
  void setMap(Bomberman_Map *_map) { map = _map; }
  irr::video::IVideoDriver *getDriver() const { return driver; }
  irr::scene::ISceneManager *getSmgr() const { return smgr; }
  irr::IrrlichtDevice *getDevice() const { return device; }
  MyEventReceiver getReceiver() const { return receiver; }
  void create(unsigned x, unsigned y, char c);
  void remove(unsigned x, unsigned y);
};

#endif
