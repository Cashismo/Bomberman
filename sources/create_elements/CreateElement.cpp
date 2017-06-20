#include "../../include/SpeedBonus.hpp"
#include "../../include/LifeBonus.hpp"
#include "../../include/BombBonus.hpp"
#include "../../include/CreateElement.hpp"
#include "../../include/UnbreakableObstacle.hpp"
#include "../../include/BreakableObstacle.hpp"
#include "../../include/ExplosionObstacle.hpp"
#include "../../include/NormalBomb.hpp"
#include "../../include/GroundObstacle.hpp"

CreateElement::CreateElement()
{
  functions[0] = &CreateElement::createSpeed;
  functions[1] = &CreateElement::createBombs;
  functions[2] = &CreateElement::createLife;
}

IElement	*CreateElement::createRandom()
{
  std::uniform_int_distribution<int>	type(0, 2);
  std::random_device			rd;
  int	i = type(rd);
  std::unordered_map<int, Func>::const_iterator it = functions.find(i);

  return ((this->*(it->second))());
}

IElement	*CreateElement::createGround()
{
  return (new GroundObstacle);
}

IElement	*CreateElement::createBomb()
{
  return (new NormalBomb);
}

IElement	*CreateElement::createExplosion()
{
  return (new ExplosionObstacle);
}

IElement        *CreateElement::createBreakable()
{
  return (new BreakableObstacle);
}

IElement	*CreateElement::createUnbreakable()
{
  return (new UnbreakableObstacle);
}

IElement	*CreateElement::createSpeed()
{
  return (new SpeedBonus);
}

IElement	*CreateElement::createBombs()
{
  return (new BombBonus);
}

IElement	*CreateElement::createLife()
{
  return (new LifeBonus);
}
