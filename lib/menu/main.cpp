#include "ConfFile.hpp"
#include "Menu.hpp"
#include <iostream>
#include <memory>

int main(void) {
  ConfFile conf("bomberman.conf");
  if (conf.openFile() == false)
    return EXIT_FAILURE;
  if (conf.parseFile() == false)
    return EXIT_FAILURE;
  conf.dumpData();
  Menu menu;
  menu.start();

  return EXIT_SUCCESS;
}
