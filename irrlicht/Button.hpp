#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include "include/irrlicht.h"
#include <string>

class Button {
public:
  Button(const irr::io::path &, const irr::io::path &,
         irr::video::IVideoDriver *, size_t, size_t);
  ~Button() {}
  void drawImage();
  void drawImageOn();

private:
  irr::video::ITexture *_image;
  irr::video::ITexture *_imageOn;
  irr::video::IVideoDriver *_driver;
  size_t _x;
  size_t _y;
};

#endif
