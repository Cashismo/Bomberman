#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "AElement.hpp"
#include <ctime>
#include <vector>

class Bomb : public AElement {
protected:
  IElement *owner;
  std::vector<std::pair<size_t, size_t>> explosion_coord;
  bomb_type type;
  int time;
  time_t start;
  int hor_ray;
  int ver_ray;
  bool exploded;

public:
  Bomb(int _hor_ray, int _ver_ray, int _time, bomb_type _t);
  virtual ~Bomb() {}
  virtual void addCoord(std::pair<int, int>);
  virtual std::vector<std::pair<size_t, size_t>> getCoords() const {
    return explosion_coord;
  }
  virtual void explose();
  virtual time_t getStart() const { return (start); }
  virtual void setStart(time_t _start) { start = _start; }
  virtual bool isExploded() const { return exploded; }
  virtual void setOwner(IElement *player) { owner = player; }

  virtual std::pair<float, float> getCoord() {
    std::pair<float, float> tmp;
    return tmp;
  }
  virtual IElement *putBomb(Bomberman_Map *) { return NULL; }
  virtual bool takeDamage() { return false; }
  virtual dir getDir() const { return RIGHT; }
  virtual bool pickBonus(IElement *) { return false; }
  virtual std::pair<int, int> getCoordBomb() {
    std::pair<float, float> tmp;
    return tmp;
  }
  virtual obstacle_type getObstacleType() const { return BREAKABLE; }
  virtual bonus_type getType() const { return SPEED; }
  virtual int getEffect() const { return 0; }
  virtual IElement *action(int, Bomberman_Map *) { return (NULL); }
  virtual IElement *go_right(Bomberman_Map *) { return (NULL); }
  virtual IElement *go_left(Bomberman_Map *) { return (NULL); }
  virtual IElement *go_up(Bomberman_Map *) { return (NULL); }
  virtual IElement *go_down(Bomberman_Map *) { return (NULL); }
  virtual bool	isExpired() const { return false; }
  virtual void	setStart() {}
  virtual void addBomb() {}
};

#endif /* !BOMB_HPP_ */
