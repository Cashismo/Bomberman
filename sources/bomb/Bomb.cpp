#include "../../include/Bomb.hpp"

Bomb::Bomb(const int & _hor_ray, const int & _ver_ray, const int & _time, const bomb_type & _t) : AElement(BOMB)
{
  type = _t;
  time = _time;
  hor_ray = _hor_ray;
  ver_ray = _ver_ray;
  exploded = false;
}

void	Bomb::addCoord(const std::pair<int, int> & coord)
{
  explosion_coord.push_back(coord);
}

void	Bomb::explose(const std::vector<std::vector<IElement *>> & map)
{
  std::pair<int, int>	coord;
  int			x;
  int			y;

  y = explosion_coord[0].first;
  x = explosion_coord[0].second;
  coord.first = y;
  for (int i = x ; i <= x + hor_ray ; i++)
    {
      if (map[y][i] && map[y][i]->getSym() == 'x')
	break ;
      if (i != x)
	{
	  coord.second = i;
	  addCoord(coord);
	}
    }
  for (int i = x; i >= x - hor_ray; i--)
    {
      if (map[y][i] && map[y][i]->getSym() == 'x')
	break ;
      if (i != x)
	{
	  coord.second = i;
	  addCoord(coord);
	}
    }
  coord.second = x;
  for (int i = y; i <= y + ver_ray; i++)
    {
      if (map[i][x] && map[i][x]->getSym() == 'x')
        break ;
      if (i != y)
	{
	  coord.first = i;
	  addCoord(coord);
	}
    }
  for (int i = y; i >= y - ver_ray; i--)
    {
      if (map[i][x] && map[i][x]->getSym() == 'x')
	break ;
      if (i != y)
	{
	  coord.first = i;
	  addCoord(coord);
	}
    }
  exploded = true;
  if (owner)
    owner->addBomb();
}
