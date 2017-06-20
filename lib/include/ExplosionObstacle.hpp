#ifndef EXPLOSIONOBSTACLE_HPP_
#define EXPLOSIONOBSTACLE_HPP_

#include "Obstacle.hpp"

class ExplosionObstacle : public Obstacle {
  std::pair<float, float> tmp;

public:
  ExplosionObstacle() : Obstacle(EXPLOSION) { sym = 'e'; }

  /*  virtual const std::pair<float, float> &getCoord() const { return tmp; }
  virtual IElement *putBomb() { return NULL; }
  virtual bool takeDamage() { return false; }
  virtual dir getDir() const { return RIGHT; }
  virtual void pickBonus(IElement *) {}
  virtual std::pair<int, int> getCoordBomb() {
    std::pair<int, int> tmp;
    return tmp;
  }
  //  virtual obstacle_type getObstacleType() const {return EXPLOSION;}
  virtual bonus_type getType() const { return SPEED; }
  virtual int getEffect() const { return 0; }
  virtual IElement *action(int) { return (NULL); }
  virtual IElement *go_right() { return (NULL); }
  virtual IElement *go_left() { return (NULL); }
  virtual IElement *go_up() { return (NULL); }
  virtual IElement *go_down() { return (NULL); }*/
};

#endif /* !EXPLOSIONOBSTACLE_HPP_ */
