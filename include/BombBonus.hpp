#ifndef	BOMBBONUS_HPP_
# define BOMBBONUS_HPP_

#include "Bonus.hpp"

class	BombBonus : public Bonus
{
public:
  BombBonus() : Bonus(BOMBS) {}
};

#endif	/* !BOMBBONUS_HPP_ */
