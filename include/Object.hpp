#ifndef OBJ_HPP_
# define OBJ_HPP_

#include <iostream>
#include <string>
#include "include/irrlicht.h"

class Object
{
  irr::scene::IAnimatedMeshSceneNode *node;
public :
  Object() { node = NULL; }
  Object(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, irr::scene::IAnimatedMesh *my_obj, irr::video::ITexture *texture);
  irr::scene::IAnimatedMeshSceneNode *getObject() const;
  void remove() { if (node) node->remove(); node = NULL; }
  void create(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver,irr::scene::IAnimatedMesh *my_obj, irr::video::ITexture *texture);
};

#endif
