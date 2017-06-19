#include "../../include/Camera.hpp"

Camera::Camera(Graphic *graphic) { _graphic = graphic; }

void Camera::SpecMode() { _graphic->getSmgr()->addCameraSceneNodeFPS(); }
void Camera::GameMode() {
  _graphic->getSmgr()->addCameraSceneNode(
      0, irr::core::vector3df(1000, 1000, 500),
      irr::core::vector3df(100, -2500, 500), 0, true);
}

void Camera::setGraphic(Graphic *graphic) { _graphic = graphic; }
