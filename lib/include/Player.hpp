#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "AElement.hpp"
#include "NormalBomb.hpp"
#include <unordered_map>
#include <utility>
#include <vector>

class Player : public AElement {
protected:
  typedef IElement *(Player::*Func)(Bomberman_Map *);

  IElement *bonus;
  std::vector<IElement *> bombs;
  std::pair<float, float> coords;
  int maxBombs;
  int nbBombs;
  int life;
  int nb_team;
  float speed;
  float previous_speed;
  dir direction;
  std::unordered_map<int, Func> conf;

public:
  Player(int _nb_team);
  virtual ~Player();
  virtual IElement *putBomb(Bomberman_Map *map);
  virtual std::pair<int, int> getCoordBomb();
  virtual dir getDir() const { return direction; }
  virtual bool pickBonus(IElement *_bonus);
  virtual std::pair<float, float> getCoord() { return coords; }
  virtual bool takeDamage();
  virtual IElement *action(int, Bomberman_Map *map);
  virtual IElement *go_right(Bomberman_Map *map);
  virtual IElement *go_left(Bomberman_Map *map);
  virtual IElement *go_up(Bomberman_Map *map);
  virtual IElement *go_down(Bomberman_Map *map);
  virtual void addBomb() { ++nbBombs; std::cout << "nbBombs in add = " << nbBombs << std::endl; }

  virtual bonus_type getType() const { return SPEED; }
  virtual int getEffect() const { return 0; }
  virtual void addCoord(std::pair<int, int>) {}
  virtual void explose() {}
  virtual void setStart(time_t _start) { static_cast<void>(_start); }
  virtual obstacle_type getObstacleType() const { return BREAKABLE; }
  virtual std::vector<std::pair<size_t, size_t>> getCoords() const {
    std::vector<std::pair<size_t, size_t>> tmp;
    return tmp;
  }
  virtual time_t getStart() const { return 1; }
  virtual bool isExploded() const { return true; }
  virtual bool	isExpired() const { return false; }
  virtual void	setStart() {}
  virtual void setOwner(IElement *player) {}
};

#endif /* !PLAYER_HPP_ */
