#ifndef OBSTACLE_HPP_
#define OBSTACLE_HPP_

#include "AElement.hpp"

class Obstacle : public AElement {
protected:
  obstacle_type type;

public:
  Obstacle(obstacle_type _type);
  virtual const obstacle_type getObstacleType() const { return type; }

  virtual const bonus_type getType() const { return LIFE; }
  virtual const int getEffect() const { return 0; }
  virtual void addCoord(const std::pair<int, int> &) {}
  virtual const time_t getStart() const { return 0; }
  virtual void setStart(const time_t & _start) {}
  virtual void explose(const std::vector<std::vector<IElement *>> & map) {}
  virtual const std::vector<std::pair<size_t, size_t>>  getCoords() const {
    std::vector<std::pair<size_t, size_t>> tmp;
    return tmp;
  }
  virtual const bool isExploded() const { return true; }
  virtual const bool	isExpired() const { return false; }
  virtual void	setStart() {}
  virtual void setOwner(Player *player) {}
};

#endif /* !OBSTACLE_HPP_ */
