#ifndef	CREATEELEMENT_HPP_
# define CREATEELEMENT_HPP_

#include <random>
#include <unordered_map>
#include "Bomb.hpp"
#include "Bonus.hpp"
#include "Obstacle.hpp"

class	CreateElement
{
public:
  CreateElement();
  IElement	*createRandom();
  IElement	*createSpeed();
  IElement	*createBombs();
  IElement	*createLife();
  IElement      *createUnbreakable();
  IElement	*createBreakable();
  IElement	*createExplosion();
  IElement	*createGround();
  IElement	*createBomb();
private:
  typedef IElement *(CreateElement::*Func)(void);
  std::unordered_map<int, Func>	functions;
};

#endif /* !CREATEELEMENT_HPP_ */
