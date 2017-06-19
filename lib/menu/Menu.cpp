#include "Menu.hpp"

static int nbIAValue;
static int nbPlayersValue;
int indexKeys;
int indexMap;
ConfFile::Data indexData;
std::string _mapName;
bool test = false;

Menu::Menu() {
  std::string tmp;
  _device = irr::createDevice(irr::video::EDT_OPENGL,
                              irr::core::dimension2d<irr::u32>(1700, 900), 40,
                              false, false, false, &_receiver);
  if (!_device)
    return;
  _driver = _device->getVideoDriver();
  _sceneManager = _device->getSceneManager();
  ConfFile conf("bomberman.conf");
  _datas = conf.getMap();
  nbIAValue = std::atoi(_datas[ConfFile::NB_AI].c_str());
  nbPlayersValue = std::atoi(_datas[ConfFile::NB_PLAYERS].c_str());
  _mapName = _datas[ConfFile::MAP];
  conf.dumpData();
  _listOfMap = readDir("maps/");
  for (const auto &e : _listOfMap) {
    std::cout << e << std::endl;
  }
  _sceneManager->addCameraSceneNode(0, irr::core::vector3df(1000, 1000, 500),
                                    irr::core::vector3df(100, -2500, 500), 0,
                                    true);
}

Menu::~Menu() {}

const std::map<ConfFile::Data, std::string> &Menu::getDatas() { return _datas; }

std::vector<std::string> Menu::readDir(const std::string &dirName) {
  DIR *openDir;
  struct dirent *content;
  std::vector<std::string> listOfMaps;

  openDir = opendir(dirName.c_str());
  content = readdir(openDir);
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

Menu::Mode Menu::validateButton() {
  _datas[ConfFile::NB_AI] = std::to_string(nbIAValue);
  _datas[ConfFile::NB_PLAYERS] = std::to_string(nbPlayersValue);
  _datas[ConfFile::MAP] = _listOfMap[indexMap];
  std::cout << "nbIAValue: " << _datas[ConfFile::NB_AI] << std::endl;
  std::cout << "nbPlayersValue: " << _datas[ConfFile::NB_PLAYERS] << std::endl;
  std::cout << "map: " << _datas[ConfFile::MAP] << std::endl;
  std::cout << "UP_1: " << _datas[ConfFile::UP_1] << std::endl;
  std::cout << "DOWN_1: " << _datas[ConfFile::DOWN_1] << std::endl;
  std::cout << "LEFT_1: " << _datas[ConfFile::LEFT_1] << std::endl;
  std::cout << "RIGHT_1: " << _datas[ConfFile::RIGHT_1] << std::endl;
  std::cout << "BOMB_1: " << _datas[ConfFile::BOMB_1] << std::endl;
  std::cout << "UP_2: " << _datas[ConfFile::UP_2] << std::endl;
  std::cout << "DOWN_2: " << _datas[ConfFile::DOWN_2] << std::endl;
  std::cout << "LEFT_2: " << _datas[ConfFile::LEFT_2] << std::endl;
  std::cout << "RIGHT_2: " << _datas[ConfFile::RIGHT_2] << std::endl;
  std::cout << "BOMB_2: " << _datas[ConfFile::BOMB_2] << std::endl;

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
    if (nbPlayersValue == 0) {
      nbPlayersValue = 0;
      return OPTION;
    }
    if ((nbPlayersValue + nbIAValue) == 4)
      if (nbPlayersValue == 4) {
        nbPlayersValue = nbPlayersValue - 1;
        return OPTION;
      }
    if ((nbPlayersValue + nbIAValue) == 4)
      return OPTION;
    nbPlayersValue = nbPlayersValue - 1;
  } else if (setClickZone(1350, 1430, 300, 360) == true) {
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

Menu::Mode Menu::clickEvent(Menu::Mode mode) {
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
    std::cout << "PLAY" << std::endl;
    return PLAY;
  case OPTION:
    if (setClickZone(30, 160, 30, 120) == true)
      return DEFAULT;
    clickOption();
    if (setClickZone(620, 1075, 670, 780) == true)
      return validateButton();
    return OPTION;
  case KEYBOARD:
    if (setClickZone(30, 160, 30, 120) == true)
      return DEFAULT;
    if (setClickZone(250, 460, 265, 320) == true) {
      test = true;
      indexData = ConfFile::UP_1;
    } else if (setClickZone(250, 460, 375, 430) == true) {
      test = true;
      indexData = ConfFile::DOWN_1;
    } else if (setClickZone(250, 460, 485, 540) == true) {
      test = true;
      indexData = ConfFile::LEFT_1;
    } else if (setClickZone(250, 460, 595, 650) == true) {
      test = true;
      indexData = ConfFile::RIGHT_1;
    } else if (setClickZone(250, 460, 705, 770) == true) {
      test = true;
      indexData = ConfFile::BOMB_1;
    } else if (setClickZone(1250, 1460, 265, 320) == true) {
      test = true;
      indexData = ConfFile::UP_2;
    } else if (setClickZone(1250, 1460, 375, 430) == true) {
      test = true;
      indexData = ConfFile::DOWN_2;
    } else if (setClickZone(1250, 1460, 485, 540) == true) {
      test = true;
      indexData = ConfFile::LEFT_2;
    } else if (setClickZone(1250, 1460, 595, 650) == true) {
      test = true;
      indexData = ConfFile::RIGHT_2;
    } else if (setClickZone(1250, 1460, 705, 780) == true) {
      test = true;
      indexData = ConfFile::BOMB_2;
    }
    std::cout << "X: " << _receiver.GetMouseState().Position.X
              << " --------- Y: " << _receiver.GetMouseState().Position.Y
              << std::endl;

    if (setClickZone(620, 1075, 670, 780) == true)
      return validateButton();
    return KEYBOARD;
  case EXIT:
    return EXIT;
  }
  return DEFAULT;
}

bool Menu::setClickZone(int x1, int x2, int y1, int y2) {
  if (_receiver.GetMouseState().Position.X > x1 &&
      _receiver.GetMouseState().Position.X < x2 &&
      _receiver.GetMouseState().Position.Y > y1 &&
      _receiver.GetMouseState().Position.Y < y2)
    return true;
  return false;
}

void Menu::start() {
  _driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
  irr::scene::ISceneNode *skybox = _sceneManager->addSkyBoxSceneNode(
      _driver->getTexture("../models/irrlicht2_up.jpg"),
      _driver->getTexture("../models/irrlicht2_dn.jpg"),
      _driver->getTexture("../models/irrlicht2_lf.jpg"),
      _driver->getTexture("../models/irrlicht2_rt.jpg"),
      _driver->getTexture("../models/irrlicht2_ft.jpg"),
      _driver->getTexture("../models/irrlicht2_bk.jpg"));
  skybox->setVisible(true);
  auto mode = DEFAULT;
  auto mode1 = DEFAULT;
  irr::video::ITexture *image = _driver->getTexture("../models/menu.png");
  irr::video::ITexture *bomb = _driver->getTexture("../models/bomb.png");
  irr::video::ITexture *options = _driver->getTexture("../models/options.png");
  irr::video::ITexture *pressKey =
      _driver->getTexture("../models/presskey.png");
  irr::video::ITexture *keyboard =
      _driver->getTexture("../models/keyboard.png");
  irr::gui::IGUIFont *font =
      _device->getGUIEnvironment()->getFont("../models/myfont3.xml");
  std::vector<bool> keys = _receiver.getKeys();
  while (_device->run()) {

    _sceneManager->drawAll();
    if (test == true) {
      for (int i = 0; i != 153; i++) {

        keys = _receiver.getKeys();
        if (keys[i] && i != 13) {
          std::cout << i << std::endl;
          _datas[indexData] = static_cast<char>(i);
          test = false;
        }
      }
      _receiver.clearKeys();
    }
    //_driver->beginScene(true, true, irr::video::SColor(0, 120, 120, 120));
    if (_receiver.GetMouseState().LeftButtonDown == true) {
      mode = clickEvent(mode1);
      _event.EventType = irr::EET_MOUSE_INPUT_EVENT;
      _event.MouseInput.Event = irr::EMIE_LMOUSE_LEFT_UP;
      _receiver.OnEvent(_event);
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
      break;
    case OPTION:
      mode1 = OPTION;
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
      font->draw(_datas[ConfFile::UP_1].c_str(),
                 irr::core::rect<irr::s32>(340, 270, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_datas[ConfFile::DOWN_1].c_str(),
                 irr::core::rect<irr::s32>(340, 385, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_datas[ConfFile::LEFT_1].c_str(),
                 irr::core::rect<irr::s32>(340, 500, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_datas[ConfFile::RIGHT_1].c_str(),
                 irr::core::rect<irr::s32>(340, 615, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_datas[ConfFile::BOMB_1].c_str(),
                 irr::core::rect<irr::s32>(340, 728, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));

      font->draw(_datas[ConfFile::UP_2].c_str(),
                 irr::core::rect<irr::s32>(1340, 270, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_datas[ConfFile::DOWN_2].c_str(),
                 irr::core::rect<irr::s32>(1340, 385, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_datas[ConfFile::LEFT_2].c_str(),
                 irr::core::rect<irr::s32>(1340, 500, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_datas[ConfFile::RIGHT_2].c_str(),
                 irr::core::rect<irr::s32>(1340, 615, 300, 50),
                 irr::video::SColor(255, 255, 255, 255));
      font->draw(_datas[ConfFile::BOMB_2].c_str(),
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
}
