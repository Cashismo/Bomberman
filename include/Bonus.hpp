#ifndef BONUS_HPP_
#define BONUS_HPP_

#include "AElement.hpp"
#include "Player.hpp"

class Bonus : public AElement {
protected:
  bonus_type type;
  int	effect;
  int	start;
  int	effect_time;

public:
  Bonus(const bonus_type & _t);
  virtual ~Bonus() {}
  virtual const bonus_type  getType() const { return type; }
  virtual const int  getEffect() const { return effect; }
  virtual const bool	isExpired() const;
  virtual void	setStart();

  virtual void addCoord(const std::pair<int, int> &) {}
  virtual void explose(const std::vector<std::vector<IElement *>> & map) {}
  virtual void setStart(const time_t & _start) { static_cast<void>(_start); }
  virtual const time_t getStart() const { return 1; }
  virtual const obstacle_type getObstacleType() const { return BREAKABLE; }
  virtual const std::vector<std::pair<size_t, size_t>> getCoords() const {
    std::vector<std::pair<size_t, size_t>> tmp;
    return tmp;
  }
  virtual const bool isExploded() const { return true; }
  virtual void setOwner(Player *player) {}
};

#endif /* !BONUS_HPP_ */
