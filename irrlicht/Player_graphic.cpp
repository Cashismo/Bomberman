#include "../include/Player_graphic.hpp"
#include <unistd.h>

Player_graphic::Player_graphic(Graphic *_graphic, int _place, int _type)
    : device(_graphic->getDevice()), place(_place), type(_type),
      graphic(_graphic) {
  irr::video::IVideoDriver *driver = device->getVideoDriver();
  irr::gui::IGUIEnvironment *env = _graphic->getEnv();
  init = true;
  graphic->setType(type, place);
  if (place == 1 && type == 0)
    graphic->addText(L"Joueur 1", 50, 800);
  if (place == 2 && type == 0)
    graphic->addText(L"Joueur 2", 475, 800);
  x = 0;
  y = 0;
  direction = 0;
}

void Player_graphic::setPos(float Y, float X) {
  if (init == true) {
    irr::video::IVideoDriver *driver = device->getVideoDriver();
    irr::scene::ISceneManager *smgr = device->getSceneManager();
    if (place == 1) {
      graphic->loadbar("assets/25_bar.png");
      player = smgr->addAnimatedMeshSceneNode(smgr->getMesh("assets/bot1.x"));
      if (!player)
        exit(-1);
    } else if (place == 2) {
      graphic->loadbar("assets/50_bar.png");
      player = smgr->addAnimatedMeshSceneNode(smgr->getMesh("assets/bot2.x"));
      if (!player)
        exit(-1);
    } else if (place == 3) {
      graphic->loadbar("assets/75_bar.png");
      player = smgr->addAnimatedMeshSceneNode(smgr->getMesh("assets/bot3.x"));
      if (!player)
        exit(-1);
    } else {
      graphic->loadbar("assets/100_bar.png");
      player = smgr->addAnimatedMeshSceneNode(smgr->getMesh("assets/bot4.x"));
      if (!player)
        exit(-1);
    }
    player->setScale(irr::core::vector3df(15, 15, 15));
    player->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    player->setAnimationSpeed(0);
  } else
    player->setAnimationSpeed(30);
  if (place == 1 && graphic->getFps() == true) {
    int tmp = 0;
    if (direction < 0)
      tmp += 100;
    else if (direction > 0)
      tmp += 300;
    camera = graphic->getSmgr()->addCameraSceneNode(
        0, irr::core::vector3df(Y + 300 + tmp, 200, X),
        irr::core::vector3df(Y - 2000, -2000, X), 0, true);
  }
  player->setPosition(irr::core::vector3df(Y, 20, X));
  init = false;
}

void Player_graphic::die() { player->remove(); }

void Player_graphic::rotate(int dir) {
  int rotation = 180;
  int dire = 0;
  int left = 0;
  int down = 0;
  int right = 0;

  if (dir == 1) {
    rotation = 0;
    left = -200;
    right = 200;
  } else if (dir == 2) {
    rotation = 90;
    dire = -1000;
    down = 200;
  } else if (dir == 3) {
    rotation = 270;
    dire = -1000;
    down = -200;
  } else {
    left = 200;
    right = -200;
  }
  if (place == 1) {
    x = left;
    if (direction == 0 || dire != 0)
      direction = dire;
  }
  player->setRotation(irr::core::vector3df(0, rotation, 0));
}

void Player_graphic::setSpeed(int nb) { player->setAnimationSpeed(nb); }

void Player_graphic::setLife(int nb_life) {
  if (type == 0)
    graphic->setLife(place - 1, nb_life);
}

void Player_graphic::setBomb(int bomb) {
  if (type == 0)
    graphic->setBomb(place - 1, bomb);
}
