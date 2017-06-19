#ifndef MYEVENTRECEIVER_HPP__
# define MYEVENTRECEIVER_HPP__

#include "include/irrlicht.h"
#include "Keycodes.h"
#include <vector>

class MyEventReceiver : public irr::IEventReceiver {
  std::vector<bool> keys;

 public:
  MyEventReceiver() {
    keys.reserve(KEY_KEY_CODES_COUNT);
    for (auto i = 0; i < KEY_KEY_CODES_COUNT;++i)
      keys.push_back(false);
  }
  const std::vector<bool> &getKeys() const { return keys; }
  void clearKeys() { std::fill(keys.begin(), keys.end(), false); }
  virtual bool OnEvent(const irr::SEvent &event);
};


#endif
