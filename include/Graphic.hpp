#ifndef GRAPHIC_HPP_
#define GRAPHIC_HPP_

//#include "Bomberman.hpp"
#include "Bomberman_Map.hpp"
#include "MyEventReceiver.hpp"
#include "Object.hpp"
#include "include/irrKlang.h"
#include "include/irrlicht.h"
#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

class Bomberman_Map;

class Graphic {
  irrklang::ISoundEngine *engine;
  irr::IrrlichtDevice *device;
  irr::video::IVideoDriver *driver;
  irr::scene::ISceneManager *smgr;
  MyEventReceiver receiver;
  irr::scene::ISceneNode *n;
  Bomberman_Map *map;
  irr::gui::IGUIEnvironment *env;
  irr::gui::IGUIFont *font;
  std::vector<std::wstring> text;
  std::vector<std::pair<int, int>> pos;

  std::vector<std::vector<Object>> objects;
  // std::vector<std::vector<Object>> fire;
  // std::vector<std::vector<Object>> bomb;
  int player_life[4][1];
  int nb_bomb[4][1];
  int last[4][1];
  int player_type[4][1];
  bool first_time;
  bool first_wall;
  irr::video::ITexture *red;
  irr::video::ITexture *grey;
  irr::video::ITexture *stone;
  irr::video::ITexture *wall;
  irr::video::ITexture *floor;
  irr::video::ITexture *aleat;
  irr::video::ITexture *fire;
  irr::video::ITexture *echap;
  irr::video::ITexture *bomb;
  irr::video::ITexture *gameover;

  irr::scene::IAnimatedMesh *obj_cube;
  irr::scene::IAnimatedMesh *obj_fire;
  irr::scene::IAnimatedMesh *obj_bomb;
  irr::scene::IAnimatedMesh *obj_aleat;

  bool fps;

public:
  void display_first();
  std::vector<Object> create_column(int id);
  void init_objects();

  Graphic();
  ~Graphic() { device->drop(); }
  void run();
  int echapView();
  bool setClickZone(int x1, int x2, int y1, int y2);
  void setMap(Bomberman_Map *_map) { map = _map; }
  irr::video::IVideoDriver *getDriver() const { return driver; }
  irr::scene::ISceneManager *getSmgr() const { return smgr; }
  void resetSmgr();
  irr::SEvent _event;

  irr::IrrlichtDevice *getDevice() const { return device; }
  irr::gui::IGUIEnvironment *getEnv() const { return env; }
  MyEventReceiver getReceiver() const { return receiver; }
  irrklang::ISoundEngine *getSound() const { return engine; }
  Bomberman_Map *getMap() const { return map; }
  void setEnv(irr::gui::IGUIEnvironment *_env);
  void create(unsigned x, unsigned y, char c);
  void remove(unsigned x, unsigned y);
  void addText(std::wstring buf, int x, int y);
  void disp_life();
  void disp_nb_bomb();
  void setLife(int nb_team, int nb_life);
  void setBomb(int nb_team, int bomb);
  void loadbar(std::string bar);
  void gameOver();
  void init();
  void setFps(bool _fps) { fps = _fps; }
  bool getFps() { return fps; }
  void setType(int _type, int nb) {
    player_type[nb - 1][0] = _type;
  } // 0 == player || 1 == bot
  void end();
};

#endif
