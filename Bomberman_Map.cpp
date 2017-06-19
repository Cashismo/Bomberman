#include "include/Bomberman_Map.hpp"
#include "include/Obstacle.hpp"
#include "include/ExplosionObstacle.hpp"
#include "include/BreakableObstacle.hpp"
#include "include/UnbreakableObstacle.hpp"
#include "include/GroundObstacle.hpp"
#include "include/CreateElement.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

Bomberman_Map::Bomberman_Map(const std::string &name) : _name(name) {
  loadMap();
}

void Bomberman_Map::setMapStr(const std::vector<std::string> &data) {
  elements.clear();
  elements.reserve(data.size());
  for (const auto &line : data)
    {
      auto tmp = create_column(line);
      tmp.shrink_to_fit();
      elements.emplace_back(std::move(tmp));
    }
}

std::vector<IElement *> Bomberman_Map::create_column(const std::string &str) {
  std::vector<IElement *> column;
  CreateElement creator;
  unsigned rows;

  rows = str.length();
  column.reserve(rows);
  for (const auto &c : str)
    {
      IElement *tmp;// = creator.create(c); // throw exceptions si mauvais element
      if (c == 'x')
	tmp = creator.createUnbreakable();
      else if (c == 'w')
	tmp = creator.createBreakable();
      else if (c == 'n')
	tmp = creator.createGround();
      else
	exit(0);
      column.emplace_back(tmp);
    }
  return column;
}



void Bomberman_Map::loadMap() {
  std::ifstream file(_name);
  std::string str;
  unsigned cols;

  cols = std::count(std::istreambuf_iterator<char>(file),
		    std::istreambuf_iterator<char>(), '\n');
  elements.reserve(cols);
  file.clear();
  file.seekg(0, std::ios::beg);
  while (std::getline(file, str))
    {
      auto tmp = create_column(str);
      tmp.shrink_to_fit();
      elements.emplace_back(std::move(tmp));
    }
  if (elements.size() < 10)
    exit(0);
}
