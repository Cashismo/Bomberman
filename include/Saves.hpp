#ifndef __SAVES_HPP__
#define __SAVES_HPP__
#include "Bomberman.hpp"
#include "Graphic.hpp"
#include "Menu.hpp"
#include <fstream>
#include <sstream>
#include <vector>

class Saves {
  Bomberman *_bomberman;
  Bomberman_Map *_map;
  std::vector<Player *> _ais;
  std::vector<Player *> _players;
  Graphic *_graphic;
  Menu _menu;
  std::ofstream file;

  void to_file(const std::stringstream &);
  void loadMap(const std::vector<std::string> &);
  void loadPlayers(const std::vector<std::string> &, bool);
  void loadBombs(const std::vector<std::string> &);

public:
  Saves(Bomberman *bomberman, Bomberman_Map *map, std::vector<Player *> &ais,
        std::vector<Player *> &players, Menu &menu, Graphic *graphic)
      : _bomberman(bomberman), _map(map), _ais(ais), _players(players),
        _menu(menu), _graphic(graphic) {}
  bool save_game(const std::string &);
  bool load_game(const std::string &);
  void setBomberman(Bomberman *bomberman) { _bomberman = bomberman; }
};

#endif
