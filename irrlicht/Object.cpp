#include "../include/Object.hpp"

Object::Object(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, irr::scene::IAnimatedMesh *my_obj , irr::video::ITexture *texture)
{
  if (my_obj)
    node = smgr->addAnimatedMeshSceneNode(my_obj);
  node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  if (texture)
    node->setMaterialTexture(0, texture);
}

irr::scene::IAnimatedMeshSceneNode *Object::getObject() const
{
  return (node);
}

void Object::create(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver,
		    irr::scene::IAnimatedMesh *my_obj, irr::video::ITexture *texture)
{

  if (my_obj)
    node = smgr->addAnimatedMeshSceneNode(my_obj);
  node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  if (texture)
    node->setMaterialTexture(0, texture);
}
