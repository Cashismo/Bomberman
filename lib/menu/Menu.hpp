#ifndef __MENU_HPP__
#define __MENU_HPP__

#include "../include/irrlicht.h"
#include "ConfFile.hpp"
#include "MenuEventReceiver.hpp"
#include <dirent.h>
#include <dlfcn.h>
#include <iostream>
#include <list>
#include <string>
#include <vector>

class Menu {
public:
  enum Mode {
    DEFAULT,
    PLAY,
    OPTION,
    KEYBOARD,
    EXIT,
  };

  Menu();
  ~Menu();
  void start();
  const std::map<ConfFile::Data, std::string> &getDatas();

private:
  Mode clickOption();
  Mode validateButton();
  std::vector<std::string> readDir(const std::string &dirName);
  std::map<ConfFile::Data, std::string> _datas;
  std::vector<std::string> _listOfMap;
  bool setClickZone(int, int, int, int);
  void selectElement(irr::video::ITexture *);
  Mode clickEvent(Mode);

  irr::SEvent _event;
  irr::IrrlichtDevice *_device;
  irr::video::IVideoDriver *_driver;
  irr::scene::ISceneManager *_sceneManager;
  MenuEventReceiver _receiver;
};

#endif
