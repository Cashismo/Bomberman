#ifndef	LIFEBONUS_HPP_
# define LIFEBONUS_HPP_

#include "Bonus.hpp"

class	LifeBonus : public Bonus
{
public:
  LifeBonus() : Bonus(LIFE) {}
};

#endif	/* !LIFEBONUS_HPP_ */
