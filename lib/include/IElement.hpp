#ifndef IELEMENT_HPP_
#define IELEMENT_HPP_

#include "Bomberman_Map.hpp"
#include <ctime>
#include <vector>

class Bomberman_Map;

enum element_type { PLAYER = 0, BONUS = 1, BOMB = 2, OBSTACLE = 3 };

enum dir { RIGHT, LEFT, UP, DOWN };

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
  virtual element_type getElementType() const = 0;
  virtual const char &getSym() const = 0;

  // Player

  virtual IElement *putBomb(Bomberman_Map *map) = 0;
  virtual dir getDir() const = 0;
  virtual bool pickBonus(IElement *) = 0;
  virtual std::pair<int, int> getCoordBomb() = 0;
  virtual std::pair<float, float> getCoord() = 0;
  virtual IElement *action(int, Bomberman_Map *map) = 0;
  virtual IElement *go_right(Bomberman_Map *map) = 0;
  virtual IElement *go_left(Bomberman_Map *map) = 0;
  virtual IElement *go_up(Bomberman_Map *map) = 0;
  virtual IElement *go_down(Bomberman_Map *map) = 0;
  virtual bool takeDamage() = 0;
  virtual void addBomb() = 0;

  // Bonus

  virtual bonus_type getType() const = 0;
  virtual int getEffect() const = 0;
  virtual bool	isExpired() const = 0;
  virtual void	setStart() = 0;


  // Bombs

  virtual time_t getStart() const = 0;
  virtual void setStart(time_t _start) = 0;
  virtual std::vector<std::pair<size_t, size_t>> getCoords() const = 0;
  virtual void addCoord(std::pair<int, int>) = 0;
  virtual void explose() = 0;
  virtual bool isExploded() const = 0;
  virtual void setOwner(IElement *player) = 0;

  // Obstacles

  virtual obstacle_type getObstacleType() const = 0;
};

#endif /* !IELEMENT_HPP_ */
