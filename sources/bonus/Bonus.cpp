#include <time.h>
#include "../../include/SpeedBonus.hpp"
#include "../../include/BombBonus.hpp"
#include "../../include/LifeBonus.hpp"
#include "../../include/Bonus.hpp"

Bonus::Bonus(const bonus_type & _t) : AElement(BONUS)
{
  if (_t == SPEED)
    effect_time = 5;
  else
    effect_time = 0;
  type = _t;
  sym = 'a';
  effect = 1;
}

const bool	Bonus::isExpired() const
{
  if (time(NULL) - start >= effect_time)
    {
      std::cout << "effet expire" << std::endl;
      return (true);
    }
  return (false);
}

void	Bonus::setStart()
{
  start = time(NULL);
}
