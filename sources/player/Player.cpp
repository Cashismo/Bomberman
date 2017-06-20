#include "../../include/Player.hpp"
#include "../../include/Bomberman_Map.hpp"
#include "../../include/ConfFile.hpp"
#include "../../include/Keycodes.h"
#include "../../include/NormalBomb.hpp"
#include <unistd.h>

std::pair<float, float> randomCoords(const std::vector<std::vector<IElement *>> & map)
{

}

Player::Player(
	       Graphic *graphic, const std::map<ConfFile::Data,
	       std::pair<std::string, KEY_CODE>> &_datas,
	       const int & _nb_team)
{
  std::vector<std::vector<IElement *>>	map = graphic->getMap()->getMap();

  nb_team = _nb_team;
  maxBombs = 1;
  nbBombs = 1;
  life = 1;
  speed = 0.1;
  previous_speed = speed;
  direction = DOWN;
  bonus = NULL;
  invincible = false;
  if (nb_team == 1) {
    if (map[1][1]->getSym() == 'n')
      {
	coords.first = 1.0;
	coords.second = 1.0;
      }
    else
      coords = randomCoords(map);
    conf[_datas.at(ConfFile::UP_1).second] = &Player::go_up;
    conf[_datas.at(ConfFile::LEFT_1).second] = &Player::go_left;
    conf[_datas.at(ConfFile::DOWN_1).second] = &Player::go_down;
    conf[_datas.at(ConfFile::RIGHT_1).second] = &Player::go_right;
    conf[_datas.at(ConfFile::BOMB_1).second] = &Player::putBomb;
  } else {
    if (map[1][map[1].size() - 2]->getSym() == 'n')
      {
	coords.first = 1.0;
	coords.second = map[2].size() - 2;
      }
    conf[_datas.at(ConfFile::UP_2).second] = &Player::go_up;
    conf[_datas.at(ConfFile::LEFT_2).second] = &Player::go_left;
    conf[_datas.at(ConfFile::DOWN_2).second] = &Player::go_down;
    conf[_datas.at(ConfFile::RIGHT_2).second] = &Player::go_right;
    conf[_datas.at(ConfFile::BOMB_2).second] = &Player::putBomb;
  }
  player_graphic = new Player_graphic(graphic, nb_team, 0);
  player_graphic->setPos(coords.first * 47, coords.second * 47);
}

Player::Player() {
}

Player::~Player() {}

bool Player::takeDamage() {
  if (invincible && time(NULL) - start_invincible <= 5)
    return false;
  invincible = false;
  life -= 1;
  player_graphic->setLife(life);
  if (life == 0)
    player_graphic->die();
  else
    {
      invincible = true;
      start_invincible = time(NULL);
    }
  return (life == 0);
}

IElement *Player::action(const int & key, Bomberman_Map *map) {
  std::unordered_map<int, Func>::const_iterator it = conf.find(key);
  IElement	*tmp;

  if (bonus && bonus->isExpired()) {
    speed = previous_speed;
    delete bonus;
    bonus = NULL;
  }
  if (it == conf.end())
    return (NULL);
  tmp = (this->*(it->second))(map);
  if (!tmp)
    {
      player_graphic->setPos(coords.first * 47, coords.second * 47);
      player_graphic->rotate(direction);
    }
  player_graphic->setBomb(nbBombs);
  return (tmp);
}

IElement *Player::go_right(const Bomberman_Map *map) {
  IElement *next = map->getMap()[static_cast<int>(coords.first)]
                                [static_cast<int>(coords.second + 0.6 + speed)];
  direction = RIGHT;
  if (!next || (next->getElementType() == OBSTACLE &&
                (next->getObstacleType() == BREAKABLE ||
                 next->getObstacleType() == UNBREAKABLE)))
    return (NULL);
  coords.second += speed;
  return (NULL);
}

IElement *Player::go_left(const Bomberman_Map *map) {
  IElement *next = map->getMap()[static_cast<int>(coords.first)]
                                [static_cast<int>(coords.second - speed)];

  direction = LEFT;
  if (!next || coords.second - speed < 0.0 ||
      (next->getElementType() == OBSTACLE &&
       (next->getObstacleType() == BREAKABLE ||
        next->getObstacleType() == UNBREAKABLE)))
    return (NULL);
  coords.second -= speed;
  return (NULL);
}

IElement *Player::go_up(const Bomberman_Map *map) {
  IElement *next = map->getMap()[static_cast<int>(coords.first - speed)]
                                [static_cast<int>(coords.second)];

  direction = UP;
  if (!next || (next->getElementType() == OBSTACLE &&
                (next->getObstacleType() == BREAKABLE ||
                 next->getObstacleType() == UNBREAKABLE)))
    return (NULL);
  coords.first -= speed;
  return (NULL);
}

IElement *Player::go_down(const Bomberman_Map *map) {
  IElement *next = map->getMap()[static_cast<int>(coords.first + 0.6 + speed)]
                                [static_cast<int>(coords.second)];

  direction = DOWN;
  if (!next || (next->getElementType() == OBSTACLE &&
                (next->getObstacleType() == BREAKABLE ||
                 next->getObstacleType() == UNBREAKABLE)))
    return (NULL);
  coords.first += speed;
  return (NULL);
}

IElement *Player::putBomb(const Bomberman_Map *map) {
  IElement *tmp = NULL;
  IElement *next;

  next = map->getMap()[static_cast<int>(coords.first)][static_cast<int>(coords.second)];
  if (nbBombs > 0 && next->getSym() == 'n') {
    tmp = new NormalBomb;
    tmp->setOwner(this);
    nbBombs -= 1;
  }
  return (tmp);
}

const std::pair<int, int> Player::getCoordBomb() {
  std::pair<int, int> coord;

  coord.first = static_cast<int>(coords.first);
  coord.second = static_cast<int>(coords.second);
  return (coord);
}

void Player::pickBonus(IElement *_bonus) {
  if (_bonus->getType() == SPEED && bonus == NULL) {
    bonus = _bonus;
    speed += bonus->getEffect() * speed;
    bonus->setStart();
  } else if (_bonus->getType() == LIFE && life == 1) {
    ++life;
    player_graphic->setLife(life);
  } else if (_bonus->getType() == BOMBS) {
    addBomb();
  }
}
