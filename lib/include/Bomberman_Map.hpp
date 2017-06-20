#ifndef	BOMBERMAN_MAP_HPP
# define BOMBERMAN_MAP_HPP

#include <vector>
#include <string>
#include "IElement.hpp"

class IElement;

class	Bomberman_Map
{
public:
  Bomberman_Map(const std::string &);
  Bomberman_Map() {}
  void loadMap();
  void setName(const std::string &name) { _name = name; }
  const std::vector<std::vector<IElement *>> &	getMap() const { return elements; }
  void setCase(IElement *elem, int y, int x) { elements[y][x] = elem; }

private:
  std::vector<IElement *> create_column(const std::string &);
  std::vector<std::vector<IElement *>>	elements;
  std::string _name;
};

#endif /* !BOMBERMAN_MAP_HPP */
