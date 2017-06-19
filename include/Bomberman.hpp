#ifndef BOMBERMAN_HPP_
#define BOMBERMAN_HPP_

#include "Bomberman_Map.hpp"
#include "Camera.hpp"
#include "CreateElement.hpp"
#include "Graphic.hpp"
#include "IElement.hpp"
#include "MyEventReceiver.hpp"
#include "Player.hpp"
#include "Player_graphic.hpp"
#include <ctime>

class Bomberman {
public:
  Bomberman(const std::vector<Player *> &_players,
            const std::vector<Player *> &_ais, Bomberman_Map *map,
            Graphic *_graphic);
  ~Bomberman();

  void run();
  void player_actions();
  void bomb_actions();
  void ai_actions();
  void add_power_up();
  irr::SEvent _event;

  void display_explosion(const IElement *bomb);
  void delete_explosion(const IElement *bomb);
  const Bomberman_Map *getBombermanMap() const { return map; }
  void setBombermanMap(Bomberman_Map *_map) { map = _map; }
  const std::vector<Player *> &getAis() const { return ais; }
  const std::vector<Player *> &getPlayers() const { return players; }
  const std::vector<IElement *> &getBombs() const { return bombs; }
  void setAis(std::vector<Player *> &_ais) { ais = _ais; }
  void setPlayers(std::vector<Player *> &_players) { players = _players; }
  void setBombs(std::vector<IElement *> &_bombs) { bombs = _bombs; }

private:
  Camera _camera;
  std::vector<Player *> ais;
  std::vector<Player *> players;
  std::vector<IElement *> bombs;
  std::vector<Player_graphic *> players_graphic;
  std::vector<Player_graphic *> ais_graphic;
  std::vector<int> died;
  Bomberman_Map *map;
  time_t t;
  Graphic *graphic;
  CreateElement element_creator;
};

#endif /* BOMBERMAN_HPP_ */
