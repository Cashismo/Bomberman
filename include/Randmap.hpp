#ifndef RANDMAP_HPP_
# define RANDMAP_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

class Randmap {
  std::vector<std::string> map;
public :
  Randmap();
  const std::vector<std::string> & getMap() {return map;}
};

#endif
