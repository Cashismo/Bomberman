#include "Button.hpp"

Button::Button(const irr::io::path &image, const irr::io::path &imageOn,
               irr::video::IVideoDriver *driver, size_t x, size_t y) {
  _image = driver->getTexture(image);
  _imageOn = driver->getTexture(imageOn);
  _driver = driver;
  _x = x;
  _y = y;
}

void Button::drawImage() {
  _driver->draw2DImage(_image, irr::core::position2di(_x, _y));
}

void Button::drawImageOn() {
  _driver->draw2DImage(_imageOn, irr::core::position2di(_x, _y));
}
