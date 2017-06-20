#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "AElement.hpp"
#include "Player.hpp"
#include <ctime>
#include <vector>

class Bomb : public AElement {
protected:
  Player *owner;
  std::vector<std::pair<size_t, size_t>> explosion_coord;
  bomb_type type;
  int time;
  time_t start;
  int hor_ray;
  int ver_ray;
  bool exploded;

public:
  Bomb(const int & _hor_ray, const int & _ver_ray, const int & _time, const bomb_type & _t);
  virtual ~Bomb() {}
  virtual void addCoord(const std::pair<int, int> &);
  virtual const std::vector<std::pair<size_t, size_t>>  getCoords() const {
    return explosion_coord;
  }
  virtual void explose(const std::vector<std::vector<IElement *>> & map);
  virtual const time_t getStart() const { return (start); }
  virtual void setStart(const time_t & _start) { start = _start; }
  virtual const bool isExploded() const { return exploded; }
  virtual void setOwner(Player *player) { owner = player; }

  virtual const obstacle_type getObstacleType() const { return BREAKABLE; }
  virtual const bonus_type getType() const { return SPEED; }
  virtual const int getEffect() const { return 0; }
  virtual const bool isExpired() const { return false; }
  virtual void	setStart() {}
};

#endif /* !BOMB_HPP_ */
