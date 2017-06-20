#ifndef IELEMENT_HPP_
#define IELEMENT_HPP_

#include "Bomberman_Map.hpp"
#include "Player.hpp"
#include <ctime>
#include <vector>

class Bomberman_Map;
class Player;

enum element_type { BONUS = 0, BOMB = 1, OBSTACLE = 2 };

enum bonus_type { SPEED = 4, BOMBS = 5, LIFE = 6 };

enum bomb_type { NORMAL, FIRE, ICE };

enum obstacle_type {
  BREAKABLE = 7,
  UNBREAKABLE = 8,
  EXPLOSION = 9,
  GROUND = 10
};

class IElement {
public:
  virtual const element_type & getElementType() const = 0;
  virtual const char &getSym() const = 0;

  // Bonus

  virtual const bonus_type getType() const = 0;
  virtual const int getEffect() const = 0;
  virtual const bool isExpired() const = 0;
  virtual void setStart() = 0;

  // Bombs

  virtual const time_t getStart() const = 0;
  virtual void setStart(const time_t & _start) = 0;
  virtual const std::vector<std::pair<size_t, size_t>> getCoords() const = 0;
  virtual void addCoord(const std::pair<int, int> &) = 0;
  virtual void explose(const std::vector<std::vector<IElement *>> & map) = 0;
  virtual const bool isExploded() const = 0;
  virtual void setOwner(Player *player) = 0;

  // Obstacles

  virtual const obstacle_type getObstacleType() const = 0;
};

#endif /* !IELEMENT_HPP_ */
