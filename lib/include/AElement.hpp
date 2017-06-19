#ifndef AELEMENT_HPP_
#define AELEMENT_HPP_

#include "IElement.hpp"
#include <iostream>

class AElement : public IElement {
protected:
  element_type t_element;
  char sym;

public:
  AElement(element_type _t) { t_element = _t; }
  virtual element_type getElementType() const { return t_element; }
  virtual const char &getSym() const { return sym; }

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
  virtual std::vector<std::pair<size_t, size_t>> getCoords() const = 0;
  virtual void addCoord(std::pair<int, int>) = 0;
  virtual void explose() = 0;
  virtual void setStart(time_t _start) = 0;
  virtual bool isExploded() const = 0;
  virtual void setOwner(IElement *player) = 0;

  // Obstacles

  virtual obstacle_type getObstacleType() const = 0;
};

#endif /* !AELEMENT_HPP_ */
