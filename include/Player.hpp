#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "ConfFile.hpp"
#include "Keycodes.h"
#include "Player_graphic.hpp"
#include "Graphic.hpp"
#include "IElement.hpp"
#include "Bomberman_Map.hpp"
#include <iostream>
#include <map>
#include <unordered_map>
#include <utility>
#include <vector>

enum dir { RIGHT = 0, LEFT = 1, UP = 2, DOWN = 3 };

class IElement;
class Bomberman_Map;
class Player_graphic;
class Graphic;

class Player {
protected:
  typedef IElement *(Player::*Func)(const Bomberman_Map *);

  IElement *bonus;
  Player_graphic *player_graphic;
  std::pair<float, float> coords;
  int maxBombs;
  int nbBombs;
  int life;
  int start_invincible;
  int nb_team;
  float speed;
  float previous_speed;
  dir direction;
  bool	invincible;
  std::unordered_map<int, Func> conf;

public:
  Player(Graphic *, const std::map<ConfFile::Data, std::pair<std::string, KEY_CODE>> &, const int &);
  Player();
  virtual ~Player();
  virtual IElement *putBomb(const Bomberman_Map *map);
  virtual const std::pair<int, int> getCoordBomb();
  virtual const dir & getDir() const { return direction; }
  virtual void pickBonus(IElement *_bonus);
  virtual const std::pair<float, float> & getCoord() { return coords; }
  virtual bool takeDamage();
  IElement *action(const int &, Bomberman_Map *map);
  IElement *go_right(const Bomberman_Map *map);
  IElement *go_left(const Bomberman_Map *map);
  IElement *go_up(const Bomberman_Map *map);
  IElement *go_down(const Bomberman_Map *map);
  virtual void addBomb() { ++nbBombs; }
  virtual IElement      *do_action(const std::vector<Player *> & players, const std::vector<Player *> & ai, const Bomberman_Map *map) { return (NULL); }
  void	setCoords(const std::pair<float, float> & _coords)  { coords = _coords; }
  void	setDir(const dir & _dir) { direction = _dir; }
  void	setHp(const int & _hp) { life = _hp; }
};

#endif /* !PLAYER_HPP_ */
