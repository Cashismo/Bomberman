#include "../include/irrlicht.h"
#include <iostream>
#include <list>
#include <stdio.h>
#include <string>
#include <vector>
#include <wchar.h>

using namespace irr;

int main()
{
  IrrlichtDevice* device = createDevice(irr::video::EDT_OPENGL,
					core::dimension2d<u32>(640, 480), 16, false, false, false, 0);

  if (device == 0)
    return 1; // could not create selected driver.

  video::IVideoDriver* driver = device->getVideoDriver();
  scene::ISceneManager* smgr = device->getSceneManager();
  scene::IAnimatedMeshSceneNode* n = 0;
  n = smgr->addAnimatedMeshSceneNode(smgr->getMesh("try.x"));
  n->setScale(irr::core::vector3df(20, 20, 20));
  smgr->addCameraSceneNode(0, irr::core::vector3df(100, 5, 100),
			   irr::core::vector3df(0, 0, 0), 0, true);
  video::SMaterial material;
  material.setTexture(0, driver->getTexture("models/Bomberman_0.bmp"));
  material.Lighting = true;
  material.NormalizeNormals = true;
  n->getMaterial(0) = material;
  //  n->setMD2Animation(scene::EMAT_POINT);
  device->getCursorControl()->setVisible(false);
  while(device->run())
    {
      driver->beginScene(true, true, irr::video::SColor(120, 120, 120, 120));
      smgr->drawAll();
      driver->endScene();
    }
  device->drop();
}
