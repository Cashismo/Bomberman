#include "../../include/Menu.hpp"
#include <unistd.h>

static int nbIAValue;
static int nbPlayersValue;
int indexKeys;
int indexMap;
int indexSave;
ConfFile::Data indexData;
std::string _mapName;
bool test = false;
bool isSave = false;

Menu::Menu(Graphic *_graphic) : graphic(_graphic) {
  _device = graphic->getDevice();
  if (!_device)
    return;
  _driver = graphic->getDriver();
  _sceneManager = _graphic->getSmgr();
  ConfFile conf("bomberman.conf");
  _datas = conf.getMap();
  nbIAValue = std::atoi(_datas[ConfFile::NB_AI].first.c_str());
  nbPlayersValue = std::atoi(_datas[ConfFile::NB_PLAYERS].first.c_str());
  _mapName = _datas[ConfFile::MAP].first;
  conf.dumpData();
  _listOfMap = readDir("maps/");
  _listOfSave = readDir("saves/");
  for (const auto &e : _listOfMap) {
    std::cout << e << std::endl;
  }
  _sceneManager->addCameraSceneNode(0, irr::core::vector3df(1000, 1000, 500),
                                    irr::core::vector3df(100, -2500, 500), 0,
                                    true);
}

Menu::~Menu() {}

const std::map<ConfFile::Data, std::pair<std::string, KEY_CODE>> &
Menu::getDatas() const {
  return _datas;
}

const std::vector<std::string> Menu::readDir(const std::string &dirName) const {
  DIR *openDir;
  struct dirent *content;
  std::vector<std::string> listOfMaps;
  openDir = opendir(dirName.c_str());
  if (openDir == NULL) {
    std::cerr << "ERROR: Cant open directory." << std::endl;
    std::exit(-1);
  }
  content = readdir(openDir);
  if (content == NULL) {
    std::cerr << "ERROR: Cant read directory." << std::endl;
    std::exit(-1);
  }
  while (content != NULL) {
    std::string name(content->d_name);
    if (content->d_name[0] != '.')
      listOfMaps.push_back(content->d_name);
    content = readdir(openDir);
  }
  return listOfMaps;
}

void Menu::selectElement(irr::video::ITexture *bomb) {
  if (setClickZone(160, 500, 420, 480) == true)
    _driver->draw2DImage(bomb, irr::core::position2di(526, 400),
                         irr::core::rect<irr::s32>(0, 0, 100, 100), 0,
                         irr::video::SColor(255, 255, 255, 255), true);
  else if (setClickZone(160, 500, 510, 560) == true)
    _driver->draw2DImage(bomb, irr::core::position2di(526, 490),
                         irr::core::rect<irr::s32>(0, 0, 100, 100), 0,
                         irr::video::SColor(255, 255, 255, 255), true);
  else if (setClickZone(160, 500, 600, 650) == true)
    _driver->draw2DImage(bomb, irr::core::position2di(526, 580),
                         irr::core::rect<irr::s32>(0, 0, 100, 100), 0,
                         irr::video::SColor(255, 255, 255, 255), true);
  else if (setClickZone(160, 500, 700, 750) == true)
    _driver->draw2DImage(bomb, irr::core::position2di(526, 670),
                         irr::core::rect<irr::s32>(0, 0, 100, 100), 0,
                         irr::video::SColor(255, 255, 255, 255), true);
}

Menu::Mode Menu::validateSave() {
  std::string tmp;
  tmp = "saves/";
  tmp += _listOfSave[indexSave];
  _datas[ConfFile::SAVE_NAME].first = _listOfSave[indexSave];
  _datas[ConfFile::SAVE_NAME].second = KEY_BACK;
  isSave = true;
  return CONTINUE;
}

Menu::Mode Menu::validateButton() {
  _datas[ConfFile::NB_AI].first = std::to_string(nbIAValue);
  _datas[ConfFile::NB_PLAYERS].first = std::to_string(nbPlayersValue);
  _datas[ConfFile::MAP].first = _listOfMap[indexMap];
  return DEFAULT;
}

Menu::Mode Menu::clickOption() {
  if (setClickZone(910, 990, 195, 250) == true) {
    if (nbIAValue == 0) {
      nbIAValue = 0;
      return OPTION;
    }
    nbIAValue = nbIAValue - 1;
  } else if (setClickZone(1350, 1430, 195, 250) == true) {
    if ((nbPlayersValue + nbIAValue) == 4)
      return OPTION;
    nbIAValue = nbIAValue + 1;
  } else if (setClickZone(910, 990, 300, 360) == true) {
    std::cout << "sqdsdq" << std::endl;
    if (nbPlayersValue == 0) {
      nbPlayersValue = 0;
      return OPTION;
    }
    if ((nbPlayersValue + nbIAValue) == 4) {
      if (nbPlayersValue == 4) {
        nbPlayersValue = nbPlayersValue - 1;
        return OPTION;
      }
    }
    nbPlayersValue = nbPlayersValue - 1;
  } else if (setClickZone(1350, 1430, 300, 360) == true) {
    if (nbPlayersValue == 2) {
      nbPlayersValue = 2;
      return OPTION;
    }
    std::cout << "lol1" << std::endl;
    if ((nbPlayersValue + nbIAValue) == 4)
      return OPTION;
    nbPlayersValue = nbPlayersValue + 1;
  } else if (setClickZone(910, 990, 405, 470) == true) {
    if (indexMap == 0) {
      indexMap = _listOfMap.size() - 1;
      return OPTION;
    }
    indexMap -= 1;
  } else if (setClickZone(1350, 1430, 405, 470) == true) {
    if (indexMap == _listOfMap.size() - 1) {
      indexMap = 0;
      return OPTION;
    }
    indexMap += 1;
  }
  return OPTION;
}

Menu::Mode Menu::clickEvent(const Menu::Mode &mode) {
  switch (mode) {
  case DEFAULT:
    if (setClickZone(160, 500, 420, 480) == true)
      return PLAY;
    else if (setClickZone(160, 500, 510, 560) == true)
      return OPTION;
    else if (setClickZone(160, 500, 600, 650) == true)
      return KEYBOARD;
    else if (setClickZone(160, 500, 700, 750) == true)
      return EXIT;
    break;
  case PLAY:
    return PLAY;
  case CONTINUE:
    if (setClickZone(590, 665, 360, 420) == true) {
      if (indexSave == 0) {
        indexSave = _listOfSave.size() - 1;
        return CONTINUE;
      }
      indexSave -= 1;
    }
    if (setClickZone(1030, 1100, 360, 420) == true) {
      if (indexSave == _listOfSave.size() - 1) {
        indexSave = 0;
        return CONTINUE;
      }
      indexSave += 1;
    }
    if (setClickZone(620, 1075, 670, 780) == true)
      return validateSave();
    if (setClickZone(30, 160, 30, 120) == true)
      return DEFAULT;
    return CONTINUE;
  case OPTION:
    clickOption();
    if (setClickZone(30, 160, 30, 120) == true)
      return DEFAULT;
    if (setClickZone(620, 1075, 670, 780) == true)
      return validateButton();
    return OPTION;
  case KEYBOARD:
    if (setClickZone(30, 160, 30, 120) == true)
      return DEFAULT;
    if (setClickZone(250, 460, 265, 320) == true) {
      test = true;
      indexData = ConfFile::UP_1;
    }
    if (setClickZone(250, 460, 375, 430) == true) {
      test = true;
      indexData = ConfFile::DOWN_1;
    }
    if (setClickZone(250, 460, 485, 540) == true) {
      test = true;
      indexData = ConfFile::LEFT_1;
    }
    if (setClickZone(250, 460, 595, 650) == true) {
      test = true;
      indexData = ConfFile::RIGHT_1;
    }
    if (setClickZone(250, 460, 705, 770) == true) {
      test = true;
      indexData = ConfFile::BOMB_1;
    }
    if (setClickZone(1250, 1460, 265, 320) == true) {
      test = true;
      indexData = ConfFile::UP_2;
    }
    if (setClickZone(1250, 1460, 375, 430) == true) {
      test = true;
      indexData = ConfFile::DOWN_2;
    }
    if (setClickZone(1250, 1460, 485, 540) == true) {
      test = true;
      indexData = ConfFile::LEFT_2;
    }
    if (setClickZone(1250, 1460, 595, 650) == true) {
      test = true;
      indexData = ConfFile::RIGHT_2;
    }
    if (setClickZone(1250, 1460, 705, 780) == true) {
      test = true;
      indexData = ConfFile::BOMB_2;
    }
    std::cout << "X: " << graphic->getReceiver().GetMouseState().Position.X
              << " --------- Y: "
              << graphic->getReceiver().GetMouseState().Position.Y << std::endl;
    if (setClickZone(620, 1075, 670, 780) == true)
      return validateButton();
    return KEYBOARD;
  case EXIT:
    return EXIT;
  }
  return DEFAULT;
}

bool Menu::setClickZone(int x1, int x2, int y1, int y2) {
  if (graphic->getReceiver().GetMouseState().Position.X > x1 &&
      graphic->getReceiver().GetMouseState().Position.X < x2 &&
      graphic->getReceiver().GetMouseState().Position.Y > y1 &&
      graphic->getReceiver().GetMouseState().Position.Y < y2)
    return true;
  return false;
}

int Menu::start() {
  _driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
  irr::scene::ISceneNode *skybox = _sceneManager->addSkyBoxSceneNode(
      _driver->getTexture("assets/irrlicht2_up.jpg"),
      _driver->getTexture("assets/irrlicht2_dn.jpg"),
      _driver->getTexture("assets/irrlicht2_lf.jpg"),
      _driver->getTexture("assets/irrlicht2_rt.jpg"),
      _driver->getTexture("assets/irrlicht2_ft.jpg"),
      _driver->getTexture("assets/irrlicht2_bk.jpg"));
  if (!skybox)
    return -1;
  skybox->setVisible(true);
  auto mode = DEFAULT;
  auto mode1 = DEFAULT;
  irr::video::ITexture *image = _driver->getTexture("assets/menu.png");
  irr::video::ITexture *bomb = _driver->getTexture("assets/bomb.png");
  irr::video::ITexture *options = _driver->getTexture("assets/options.png");
  irr::video::ITexture *pressKey = _driver->getTexture("assets/presskey.png");
  irr::video::ITexture *keyboard = _driver->getTexture("assets/keyboard.png");
  irr::video::ITexture *continueI = _driver->getTexture("assets/continue.png");

  if (!image || !bomb || !options || !pressKey || !keyboard || !continueI)
    return -1;

  irr::video::ITexture *map;
  std::string tmp;

  irr::gui::IGUIFont *font =
      _device->getGUIEnvironment()->getFont("assets/myfont3.xml");
  if (!font)
    return -1;
  std::vector<bool> keys = graphic->getReceiver().getKeys();
  while (_device->run()) {
    _sceneManager->drawAll();
    if (test == true) {
      for (int i = 0; i != 153; i++) {

        keys = graphic->getReceiver().getKeys();
        if (keys[i] && i != 13) {
          std::cout << i << std::endl;

          _datas[indexData].first = static_cast<char>(i);
          _datas[indexData].second = static_cast<KEY_CODE>(i);
          test = false;
        }
      }
      graphic->getReceiver().clearKeys();
    }
    if (graphic->getReceiver().GetMouseState().LeftButtonDown == true) {
      mode = clickEvent(mode1);
      _event.EventType = irr::EET_MOUSE_INPUT_EVENT;
      _event.MouseInput.Event = irr::EMIE_LMOUSE_LEFT_UP;
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      graphic->getReceiver().OnEvent(_event);
    }
    switch (mode) {
    case DEFAULT:
      mode1 = DEFAULT;
      selectElement(bomb);
      _driver->draw2DImage(image, irr::core::position2di(0, 0),
                           irr::core::rect<irr::s32>(0, 0, 1700, 900), 0,
                           irr::video::SColor(255, 255, 255, 255), true);
      break;
    case PLAY:
      mode1 = PLAY;
      return 1;
    case CONTINUE:
      mode1 = CONTINUE;
      _driver->draw2DImage(continueI, irr::core::position2di(0, 0),
                           irr::core::rect<irr::s32>(0, 0, 1700, 900), 0,
                           irr::video::SColor(255, 255, 255, 255), true);
      font->draw(_listOfSave[indexSave].c_str(),
                 irr::core::rect<irr::s32>(750, 368, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      if (isSave == true)
        return 2;
      break;
    case OPTION:
      mode1 = OPTION;
      tmp = "assets/";
      tmp += _listOfMap[indexMap];
      if (tmp.find(".") == std::string::npos)
        tmp += ".txt";
      tmp.replace(tmp.find("."), tmp.size(), ".png");
      map = _driver->getTexture(tmp.c_str());
      if (!map) {
        map = _driver->getTexture("assets/notFound.png");
        if (!map)
          return -1;
      }
      _driver->draw2DImage(map, irr::core::position2di(538, 190),
                           irr::core::rect<irr::s32>(0, 0, 300, 300), 0,
                           irr::video::SColor(255, 255, 255, 255), true);
      _driver->draw2DImage(options, irr::core::position2di(0, 0),
                           irr::core::rect<irr::s32>(0, 0, 1700, 900), 0,
                           irr::video::SColor(255, 255, 255, 255), true);
      font->draw(std::to_wstring(nbIAValue).c_str(),
                 irr::core::rect<irr::s32>(1155, 200, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(std::to_wstring(nbPlayersValue).c_str(),
                 irr::core::rect<irr::s32>(1155, 315, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_listOfMap[indexMap].c_str(),
                 irr::core::rect<irr::s32>(1090, 430, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      break;
    case KEYBOARD:
      mode1 = KEYBOARD;
      _driver->draw2DImage(keyboard, irr::core::position2di(0, 0),
                           irr::core::rect<irr::s32>(0, 0, 1700, 900), 0,
                           irr::video::SColor(255, 255, 255, 255), true);
      font->draw(_datas[ConfFile::UP_1].first.c_str(),
                 irr::core::rect<irr::s32>(340, 270, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_datas[ConfFile::DOWN_1].first.c_str(),
                 irr::core::rect<irr::s32>(340, 385, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_datas[ConfFile::LEFT_1].first.c_str(),
                 irr::core::rect<irr::s32>(340, 500, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_datas[ConfFile::RIGHT_1].first.c_str(),
                 irr::core::rect<irr::s32>(340, 615, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_datas[ConfFile::BOMB_1].first.c_str(),
                 irr::core::rect<irr::s32>(340, 728, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));

      font->draw(_datas[ConfFile::UP_2].first.c_str(),
                 irr::core::rect<irr::s32>(1340, 270, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_datas[ConfFile::DOWN_2].first.c_str(),
                 irr::core::rect<irr::s32>(1340, 385, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_datas[ConfFile::LEFT_2].first.c_str(),
                 irr::core::rect<irr::s32>(1340, 500, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_datas[ConfFile::RIGHT_2].first.c_str(),
                 irr::core::rect<irr::s32>(1340, 615, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_datas[ConfFile::BOMB_2].first.c_str(),
                 irr::core::rect<irr::s32>(1340, 730, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      if (test == true)
        _driver->draw2DImage(pressKey, irr::core::position2di(0, 0),
                             irr::core::rect<irr::s32>(0, 0, 1700, 900), 0,
                             irr::video::SColor(255, 255, 255, 255), true);
      break;
    case EXIT:
      mode1 = EXIT;
      exit(EXIT_SUCCESS);
    }
    _driver->endScene();
  }
  _device->drop();
  return 0;
}
