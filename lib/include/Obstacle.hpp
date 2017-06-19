#ifndef OBSTACLE_HPP_
#define OBSTACLE_HPP_

#include "AElement.hpp"

class Obstacle : public AElement {
protected:
  obstacle_type type;

public:
  Obstacle(obstacle_type _type);
  virtual obstacle_type getObstacleType() const { return type; }

  virtual std::pair<float, float> getCoord() {
    std::pair<float, float> tmp;
    return tmp;
  }
  virtual bonus_type getType() const { return LIFE; }
  virtual int getEffect() const { return 0; }
  virtual void move() {}
  virtual IElement *putBomb(Bomberman_Map *map) { return NULL; }
  virtual dir getDir() const { return RIGHT; }
  virtual bool pickBonus(IElement *) { return false; }
  virtual bool takeDamage() { return false; }
  virtual std::pair<int, int> getCoordBomb() {
    std::pair<int, int> tmp;
    return tmp;
  }
  virtual void addCoord(std::pair<int, int>) {}
  virtual time_t getStart() const { return 0; }
  virtual void setStart(time_t _start) {}
  virtual void explose() {}
  virtual std::vector<std::pair<size_t, size_t>> getCoords() const {
    std::vector<std::pair<size_t, size_t>> tmp;
    return tmp;
  }
  virtual IElement *action(int, Bomberman_Map *) { return (NULL); }
  virtual IElement *go_right(Bomberman_Map *) { return (NULL); }
  virtual IElement *go_left(Bomberman_Map *) { return (NULL); }
  virtual IElement *go_up(Bomberman_Map *) { return (NULL); }
  virtual IElement *go_down(Bomberman_Map *) { return (NULL); }
  virtual bool isExploded() const { return true; }
  virtual bool	isExpired() const { return false; }
  virtual void	setStart() {}
  virtual void setOwner(IElement *player) {}
  virtual void addBomb() {}
};

#endif /* !OBSTACLE_HPP_ */
