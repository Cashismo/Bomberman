#ifndef AELEMENT_HPP_
#define AELEMENT_HPP_

#include "IElement.hpp"
#include <iostream>

class AElement : public IElement {
protected:
  element_type t_element;
  char sym;

public:
  AElement(const element_type & _t) { t_element = _t; }
  virtual const element_type & getElementType() const { return t_element; }
  virtual const char &getSym() const { return sym; }

  // Bonus

  virtual const bonus_type getType() const = 0;
  virtual const int getEffect() const = 0;
  virtual const bool isExpired() const = 0;
  virtual void	setStart() = 0;

  // Bombs

  virtual const time_t getStart() const = 0;
  virtual const std::vector<std::pair<size_t, size_t>> getCoords() const = 0;
  virtual void addCoord(const std::pair<int, int>& ) = 0;
  virtual void explose(const std::vector<std::vector<IElement *>> & map) = 0;
  virtual void setStart(const time_t & _start) = 0;
  virtual const bool isExploded() const = 0;
  virtual void setOwner(Player *player) = 0;

  // Obstacles

  virtual const obstacle_type getObstacleType() const = 0;
};

#endif /* !AELEMENT_HPP_ */
