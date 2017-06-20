#include "../../include/Intro.hpp"

Intro::Intro(Graphic *graphic) { _graphic = graphic; }

Intro::~Intro() {}

void Intro::play() {

  player = _graphic->getSmgr()->addAnimatedMeshSceneNode(
      _graphic->getSmgr()->getMesh("assets/test.x"));
  player->setScale(irr::core::vector3df(100, 100, 100));
  player->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  player->setPosition(irr::core::vector3df(100, -200, 1200));

  _graphic->getSmgr()->addCameraSceneNode(0, irr::core::vector3df(700, 10, 200),
                                          irr::core::vector3df(10, 10, 500), 0,
                                          true);
  int k = 0;
  int pos = 1200;
  while (42) {
    if (k == 800) {
      irr::scene::IAnimatedMesh *my_obj =
          _graphic->getSmgr()->getMesh("assets/bomb.obj");

      bomb = _graphic->getSmgr()->addAnimatedMeshSceneNode(my_obj);
      bomb->setScale(irr::core::vector3df(3, 3, 3));
      bomb->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      bomb->setPosition(irr::core::vector3df(100, -200, 600));
      bomb->setMaterialTexture(0, _graphic->getDriver()->getTexture(""));
    }
    _graphic->getDevice()->run();
    _graphic->getDriver()->beginScene(true, true,
                                      irr::video::SColor(255, 255, 255, 255));
    _graphic->getSmgr()->drawAll();
    _graphic->getDriver()->endScene();
    player->setPosition(irr::core::vector3df(100, -200, pos));
    if (k == 1400) {
      _graphic->getSound()->play2D("sounds/boom.wav");
    }
    if (k >= 1600) {
      _graphic->getDriver()->beginScene(true, true,
                                        irr::video::SColor(255, 255, 255, 255));

      _graphic->getDriver()->endScene();
      break;
    }
    k++;
    pos -= 1;
  }

  std::this_thread::sleep_for(std::chrono::seconds(2));
  player->setPosition(irr::core::vector3df(100, -1000, 100));
  _graphic->getSmgr()->addCameraSceneNode(
      0, irr::core::vector3df(1000, 1000, 500),
      irr::core::vector3df(100, -2500, 500), 0, true);
  player->remove();
  bomb->remove();
}
