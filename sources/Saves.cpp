#include "../include/Saves.hpp"
#include "../include/AI.hpp"
#include "../include/Bomberman_Map.hpp"
#include <cstring>
#include <iostream>

void Saves::to_file(const std::stringstream &string) {
  char key = 'l';
  std::string crypted;
  std::string base = string.str();

  for (int temp = 0; temp < base.size(); temp++)
    crypted += base[temp] ^ key;
  std::cout << crypted.size() << std::endl;
  file << crypted << std::endl;
}

bool Saves::save_game(const std::string &name) {
  file.open(name);
  std::wstring str;
  std::stringstream ss;

  if (!file.is_open())
    return false;
  ss << "[MAP]" << std::endl;
  for (const auto &i : _bomberman->getBombermanMap()->getMap()) {
    for (const auto &j : i)
      ss << j->getSym();
    ss << std::endl;
  }
  int nb = 1;
  for (const auto &i : _bomberman->getAis()) {
    ss << "[AI " << nb << "]" << std::endl;
    ss << "hp=" << std::endl;
    ss << "coords=" << i->getCoord().first << "," << i->getCoord().second
       << std::endl;
    ss << "dir=" << i->getDir() << std::endl;
    ss << "team=" << std::endl;
    ++nb;
  }
  nb = 1;
  for (const auto &i : _bomberman->getPlayers()) {
    ss << "[PLAYER " << nb << "]" << std::endl;
    ss << "hp=" << std::endl;
    ss << "coords=" << i->getCoord().first << "," << i->getCoord().second
       << std::endl;
    ss << "dir=" << i->getDir() << std::endl;
    ss << "team=" << std::endl;
    ++nb;
  }
  nb = 1;
  for (const auto &i : _bomberman->getBombs()) {
    ss << "[BOMB " << nb << "]" << std::endl;
    ss << "exploded=" << i->isExploded() << std::endl;
    for (const auto &j : i->getCoords())
      ss << "coords=" << j.first << "," << j.second << ":" << std::endl;
    ++nb;
  }
  to_file(ss);
  return true;
}

void Saves::loadMap(const std::vector<std::string> &data) {
  unsigned i;
  std::vector<std::string> map_str;

  if (data.empty())
    std::exit(0);
  for (i = 1; data[i][0] == 'x'; ++i)
    map_str.push_back(data[i]);
  _map->setMapStr(map_str);
  _bomberman->setBombermanMap(_map);
}

void Saves::loadPlayers(const std::vector<std::string> &data, bool ai) {
  unsigned i;
  unsigned nb_joueur = 0;

  for (i = 0; i < data.size() &&
              std::strncmp(data[i].c_str(), ai ? "[AI" : "[PLAYER", ai ? 3 : 7);
       ++i)
    std::cout << data[i].c_str() << std::endl;
  ;
  unsigned nb_team = 1;
  unsigned hp = 2;
  unsigned _dir = 0;
  std::pair<float, float> coords(0, 0);

  for (; i < data.size() &&
         !std::strncmp(data[i].c_str(), ai ? "[AI" : "[PLAYER", ai ? 3 : 7);) {
    int start = i;
    for (i += 1; i < data.size() && i < start + 5; ++i) {
      std::string first, second;
      first = data[i].substr(0, data[i].find("=", 0));
      second = data[i].substr(data[i].find("=", 0) + 1, data[i].size());
      std::cout << first << std::endl;
      std::cout << second << std::endl;
      try {
        if (first == "hp")
          hp = std::stoi(second);
        else if (first == "nb_team")
          nb_team = std::stoi(second);
        else if (first == "dir")
          _dir = std::stoi(second);
        else if (first == "coords") {
          coords.first = std::stoi(second.substr(0, second.find(",", 0)));
          coords.second =
              std::stoi(second.substr(second.find(",", 0) + 1, second.size()));
        }
      } catch (...) {
      }
    }
    Player *elem = ai ? new AI(_graphic, 3)
                      : new Player(_graphic, _menu.getDatas(), nb_joueur++);
    elem->setHp(1);
    elem->setDir(static_cast<dir>(_dir));
    elem->setCoords(coords);
    ai ? _ais.push_back(elem) : _players.push_back(elem);
    std::cout << data[i] << std::endl;
  }

  ai ? _bomberman->setAis(_ais) : _bomberman->setPlayers(_players);
}

bool Saves::load_game(const std::string &name) {
  char key = 'l';
  std::string line;
  std::string _file;
  std::ifstream file;
  std::vector<std::string> data;

  file.open(name);
  if (!file.is_open())
    return false;

  while (std::getline(file, line, (char)('\n' ^ key)))
    data.push_back(line);
  for (auto &line : data)
    for (auto &c : line)
      c ^= key;
  loadMap(data);
  _ais.clear();
  loadPlayers(data, true);
  _players.clear();
  loadPlayers(data, false);
  return true;
}
