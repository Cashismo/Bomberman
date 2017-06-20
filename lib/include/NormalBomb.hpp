#ifndef	NORMALBOMB_HPP_
# define NORMALBOMB_HPP_

#include "Bomb.hpp"

class	NormalBomb : public Bomb
{
public:
  NormalBomb() : Bomb(3, 3, 3, NORMAL) {sym = 'b';}
};

#endif	/* !NORMALBOMB_HPP_ */
