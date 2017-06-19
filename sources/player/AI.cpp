#include <math.h>
#include "../../include/AI.hpp"

AI::AI(Graphic *graphic, const int & _nb_team) : Player()
{
  std::vector<std::vector<IElement *>>	map = graphic->getMap()->getMap();
  nb_team = _nb_team;
  maxBombs = 1;
  nbBombs = 1;
  life = 1;
  speed = 0.1;
  previous_speed = speed;
  direction = DOWN;
  bonus	= NULL;
  if (nb_team == 1 && map[1][1]->getSym() == 'n')
    {
      coords.first = 1.0;
      coords.second = 1.0;
    }
  else if (nb_team == 2 && map[1][map[1].size() - 2]->getSym() == 'n')
    {
      coords.first = 1;
      coords.second = map[1].size() - 2;
    }
  else if (nb_team == 3 && map[map.size() - 2][1]->getSym() == 'n')
    {
      coords.first = map.size() - 2;
      coords.second = 1;
    }
  else if (nb_team == 4 && map[map.size() - 2][map[map.size() - 2].size() - 2]->getSym() == 'n')
    {
      coords.first = map.size() - 2;
      coords.second = map[map.size() - 2].size() - 2;
    }
  conf[0] = &Player::go_up;
  conf[1] = &Player::go_left;
  conf[2] = &Player::go_down;
  conf[3] = &Player::go_right;
  conf[4] = &Player::putBomb;
  player_graphic = new Player_graphic(graphic, nb_team, 1);
  player_graphic->setPos(coords.first * 47, coords.second * 47);
}

const bool		AI::up(const std::vector<std::vector<IElement *>> & map)
{
  IElement *next = map[static_cast<int>(coords.first - speed)]
                                [static_cast<int>(coords.second)];
  char c = next->getSym();

  if (!next || c == 'w' || c == 'x' || isBombUp(map))
    return (false);
  direction = UP;
  coords.first -= speed;
  return (true);
}

const bool	       AI::down(const std::vector<std::vector<IElement *>> & map) {
  IElement *next = map[static_cast<int>(coords.first + 0.6 + speed)]
                                [static_cast<int>(coords.second)];
  char c = next->getSym();

  if (!next || c == 'w' || c == 'x' || isBombDown(map))
    return (false);
  direction = DOWN;
  coords.first += speed;
  return (true);
}

const bool		AI::left(const std::vector<std::vector<IElement *>> & map) {
  IElement *next = map[static_cast<int>(coords.first)]
                                [static_cast<int>(coords.second - speed)];
  char c = next->getSym();

  if (!next || coords.second - speed < 0.0 ||
      c == 'w' || c == 'x' || isBombLeft(map))
    return (false);
  direction = LEFT;
  coords.second -= speed;
  return (true);
}

const bool		AI::right(const std::vector<std::vector<IElement *>> & map) {
  IElement *next = map[static_cast<int>(coords.first)]
                                [static_cast<int>(coords.second + 0.6 + speed)];
  char	c = next->getSym();

  if (!next || c == 'w' || c == 'x' || isBombRight(map))
    return (false);
  direction = RIGHT;
  coords.second += speed;
  return (true);
}

const bool		AI::isBombUp(const std::vector<std::vector<IElement *>> & map) const
{
  int	y = static_cast<int>(coords.first);
  int	x = static_cast<int>(coords.second);
  int	start = y - 4;
  char	c;

  if (start < 0)
    start = 0;
  while (start < y)
    {
      if ((c = map[start][x]->getSym() == 'b')
	  || c == 'e')
	return (true);
      ++start;
    }
  return (false);
}

const bool            AI::isBombDown(const std::vector<std::vector<IElement *>> & map) const
{
  int	y = static_cast<int>(coords.first);
  int	x = static_cast<int>(coords.second);
  int   start = y + 4;
  char	c;

  if (start > map.size() - 1)
    start = map.size() - 1;
  while (start > y)
    {
      if ((c = map[start][x]->getSym()) == 'b'
	  || c == 'e')
	return (true);
      --start;
    }
  return (false);
}

const bool		AI::isBombLeft(const std::vector<std::vector<IElement *>> & map) const
{
  int	y = static_cast<int>(coords.first);
  int	x = static_cast<int>(coords.second);
  int	start = x - 4;
  char	c;

  if (start < 0)
    start = 0;
  while (start < x)
    {
      if ((c = map[y][start]->getSym()) == 'b'
	  || c == 'e')
	return (true);
      ++start;
    }
  return (false);
}

const bool            AI::isBombRight(const std::vector<std::vector<IElement *>> & map) const
{
  int	y = static_cast<int>(coords.first);
  int	x = static_cast<int>(coords.second);
  int   start = x + 4;
  char	c;

  if (start > map[y].size() - 1)
    start = map[y].size() - 1;
  while (start > x)
    {
      if ((c = map[y][start]->getSym()) == 'b' || c == 'e')
	return (true);
      --start;
    }
  return (false);
}

const bool		AI::possibleToMove(const std::vector<std::vector<IElement *>> & map) const
{
  int	y = static_cast<int>(coords.first);
  int	x = static_cast<int>(coords.second);
  char	c;

  if (direction == RIGHT)
    return ((c == map[y + speed][x + 1]->getSym()) == 'n'
	    || c == 'a');
  if (direction == LEFT)
    return ((c = map[y - speed][x - 1]->getSym()) == 'n'
	    || c == 'a');
  if (direction == DOWN)
    return ((c = map[y + speed][x]->getSym()) == 'n'
	    || c == 'a');
  if (direction == UP)
    return ((c = map[y - speed][x]->getSym() == 'n') ||
	    c == 'a');
  return (false);
}

const bool		AI::isBreakableBlock(const std::vector<std::vector<IElement *>> & map) const
{
  int	start_x = static_cast<int>(coords.second) - 1;
  int	start_y = static_cast<int>(coords.first) - 1;
  int	end_x = static_cast<int>(coords.second) + 1;
  int	end_y =  static_cast<int>(coords.first) + 1;

  if (possibleToMove(map))
    return (false);
  if (start_x < 0)
    start_x = 0;
  if (start_y < 0)
    start_y = 0;
  if (end_x > map[static_cast<int>(coords.first)].size() - 1)
    end_x = map[static_cast<int>(coords.first)].size() - 1;
  if (end_y > map.size() - 1)
    end_y = map.size() - 1;
  for (int y = start_y ; y < end_y ; y++)
    {
      if (map[y][coords.second]->getSym() == 'w')
	return (true);
    }
  for (int x = start_x ; x < end_x ; x++)
    {
      if (map[coords.first][x]->getSym() == 'w')
	return (true);
    }
  return (false);
}

IElement	*AI::aggressiveAction(const std::vector<Player *> & players, const std::vector<Player *> & ai, const Bomberman_Map *map)
{
  float         min;
  float         distance_tmp;
  IElement      *bomb;
  Player	*tmp;
  std::pair<float, float>       coord_player;
  std::vector<std::vector<IElement *>>  _map = map->getMap();

  min = 10000000;
  for (const auto & play : players)
    {
      if (min > (distance_tmp = getDistanceWith(play)))
        {
          tmp = play;
          min = distance_tmp;
        }
    }
  for (const auto & play : ai)
    {
      if (min > (distance_tmp = getDistanceWith(play)) && distance_tmp != 0)
	{
          tmp = play;
          min = distance_tmp;
        }
    }
  if (tmp)
    coord_player = tmp->getCoord();
  if ((sqrt(min) <= 4 || isBreakableBlock(_map)) && (bomb = putBomb(map)))
    {
      if (direction == RIGHT)
	direction = LEFT;
      else if (direction == LEFT)
	direction = RIGHT;
      else if (direction == UP)
	direction = DOWN;
      else if (direction == DOWN)
	direction = UP;
      return (bomb);
    }
  if (coords.first > coord_player.first || isBombUp(map->getMap()))
    up(_map);
  if (coords.first < coord_player.first || isBombDown(map->getMap()))
    down(_map);
  if (coords.second > coord_player.second || isBombLeft(map->getMap()))
    left(_map);
  if (coords.second < coord_player.second || isBombRight(map->getMap()))
    right(_map);
  player_graphic->setPos(coords.first * 47, coords.second * 47);
  player_graphic->rotate(direction);
  return (NULL);
}

const bool		AI::forward(const std::vector<std::vector<IElement *>> & map, int _dir)
{
  if (direction == RIGHT)
    return (right(map));
  if (direction == LEFT)
    return (left(map));
  if (direction == UP)
    return (up(map));
  return (down(map));
}

const bool		AI::escapeBomb(const std::vector<std::vector<IElement *>> & map)
{
  if (map[coords.first][coords.second]->getSym() == 'b'
      && !forward(map, 7) && !down(map) && !right(map) && !left(map) && !up(map))
    return (false);
  if ((isBombUp(map) && !forward(map, UP) && !down(map) && !right(map) && !left(map))
      || (isBombDown(map) && !forward(map, DOWN) && !up(map) && !left(map) && !right(map))
      || (isBombRight(map) && !forward(map, RIGHT) && !left(map) && !up(map) && !down(map))
      || (isBombLeft(map) && !forward(map, LEFT) && !right(map) && !up(map) && !down(map)))
    return (true);
  return (false);
}

IElement	*AI::fugitiveAction(const std::vector<Player *> & players, const std::vector<Player *> & ai, const Bomberman_Map *map)
{
  float         min;
  float         distance_tmp;
  Player	*tmp;
  std::pair<float, float>       coord_player;
  std::vector<std::vector<IElement *>>  _map = map->getMap();

  min = 10000000;
  for (const auto & play : players)
    {
      if (min > (distance_tmp = getDistanceWith(play)))
        {
          tmp = play;
          min = distance_tmp;
        }
    }
  for (const auto & play : ai)
    {
      if (min > (distance_tmp = getDistanceWith(play)) && distance_tmp != 0)
        {
          tmp = play;
          min = distance_tmp;
        }
    }
  if (!escapeBomb(_map) && !forward(_map, direction))
    {
      if (!isBombDown(map->getMap()))
	down(_map);
      else if (!isBombUp(map->getMap()))
	up(_map);
      else if (!isBombLeft(map->getMap()))
	left(_map);
      else if (!isBombRight(map->getMap()))
	right(_map);
    }
  player_graphic->setPos(coords.first * 47, coords.second * 47);
  player_graphic->rotate(direction);
  return (NULL);
}

IElement	*AI::do_action(const std::vector<Player *> & players, const std::vector<Player *> & ai, const Bomberman_Map *map)
{
  if (nbBombs <= 0)
    return fugitiveAction(players, ai, map);
  return aggressiveAction(players, ai, map);
}

const float				AI::getDistanceWith(Player *player) const
{
  std::pair<float, float>	coord = player->getCoord();

  return ((coord.second - coords.second) * (coord.second - coords.second))
    + ((coord.first - coords.first) * (coord.first - coords.first));
}
