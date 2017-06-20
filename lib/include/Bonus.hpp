#ifndef BONUS_HPP_
#define BONUS_HPP_

#include "AElement.hpp"

class Bonus : public AElement {
protected:
  bonus_type type;
  int	effect;
  int	start;
  int	effect_time;

public:
  Bonus(bonus_type _t);
  virtual ~Bonus() {}
  virtual bonus_type getType() const { return type; }
  virtual int getEffect() const { return effect; }
  virtual bool	isExpired() const;
  virtual void	setStart();


  virtual std::pair<float, float> getCoord() {
    std::pair<float, float> tmp;
    return tmp;
  }
  virtual IElement *putBomb(Bomberman_Map *map) {
    static_cast<void>(map);
    return NULL;
  }
  virtual dir getDir() const { return RIGHT; }
  virtual bool pickBonus(IElement *) { return false; }
  virtual bool takeDamage() { return false; }
  virtual std::pair<int, int> getCoordBomb() {
    std::pair<int, int> tmp;
    return tmp;
  }
  virtual void addCoord(std::pair<int, int>) {}
  virtual void explose() {}
  virtual void setStart(time_t _start) { static_cast<void>(_start); }
  virtual time_t getStart() const { return 1; }
  virtual obstacle_type getObstacleType() const { return BREAKABLE; }
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
  virtual void setOwner(IElement *player) {}
  virtual void addBomb() {}
};

#endif /* !BONUS_HPP_ */
