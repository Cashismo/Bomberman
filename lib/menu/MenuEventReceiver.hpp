#ifndef __MENUEVENTRECEIVER_HPP__
#define __MENUEVENTRECEIVER_HPP__

#include "Keycodes.h"
#include "include/irrlicht.h"
#include <vector>

class MenuEventReceiver : public irr::IEventReceiver {
public:
  struct SMouseState {
    irr::core::position2di Position;
    bool LeftButtonDown;
    SMouseState() : LeftButtonDown(false) {}
  } MouseState;

  virtual bool OnEvent(const irr::SEvent &event) {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT &&
        event.KeyInput.Key != 13) {
      if (event.KeyInput.PressedDown)
        keys[event.KeyInput.Key] = true;
      else
        keys[event.KeyInput.Key] = false;
    }

    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
      switch (event.MouseInput.Event) {
      case irr::EMIE_LMOUSE_PRESSED_DOWN:
        MouseState.LeftButtonDown = true;
        break;
      case irr::EMIE_LMOUSE_LEFT_UP:
        MouseState.LeftButtonDown = false;
        break;
      case irr::EMIE_MOUSE_MOVED:
        MouseState.Position.X = event.MouseInput.X;
        MouseState.Position.Y = event.MouseInput.Y;
        break;
      default:
        break;
      }
    }
    return false;
  }

  const std::vector<bool> &getKeys() const { return keys; }
  void clearKeys() { std::fill(keys.begin(), keys.end(), false); }
  const SMouseState &GetMouseState(void) const { return MouseState; }

  MenuEventReceiver() {
    keys.reserve(KEY_KEY_CODES_COUNT);
    for (auto i = 0; i < KEY_KEY_CODES_COUNT; ++i)
      keys.push_back(false);
  }

private:
  std::vector<bool> keys;
};

#endif
