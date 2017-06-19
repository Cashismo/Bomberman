#ifndef __MENU_HPP__
#define __MENU_HPP__

#include "ConfFile.hpp"
#include "Graphic.hpp"
#include "MyEventReceiver.hpp"
#include "include/irrlicht.h"
#include <chrono>
#include <dirent.h>
#include <dlfcn.h>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

class Menu {
public:
  enum Mode {
    DEFAULT,
    PLAY,
    CONTINUE,
    OPTION,
    KEYBOARD,
    EXIT,
  };

  Menu(Graphic *_graphic);
  ~Menu();
  int start();
  const std::map<ConfFile::Data, std::pair<std::string, KEY_CODE>> &
  getDatas() const;

private:
  Mode clickOption();
  Mode validateButton();
  Mode validateSave();
  const std::vector<std::string> readDir(const std::string &dirName) const;
  std::map<ConfFile::Data, std::pair<std::string, KEY_CODE>> _datas;
  std::vector<std::string> _listOfMap;
  std::vector<std::string> _listOfSave;
  bool setClickZone(int, int, int, int);
  void selectElement(irr::video::ITexture *);
  Mode clickEvent(const Mode &);

  irr::SEvent _event;
  Graphic *graphic;
  irr::IrrlichtDevice *_device;
  irr::video::IVideoDriver *_driver;
  irr::scene::ISceneManager *_sceneManager;
  MyEventReceiver _receiver;
};

#endif
