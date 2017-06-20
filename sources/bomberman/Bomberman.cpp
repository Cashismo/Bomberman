#include "../../include/Bomberman.hpp"
#include "../../include/AI.hpp"
#include <algorithm>
#include <ctime>
#include <random>
#include <unistd.h>

Bomberman::Bomberman(const std::vector<Player *> &_players,
                     const std::vector<Player *> &_ais, Bomberman_Map *_map,
                    Graphic *_graphic)
    : players(_players), map(_map), graphic(_graphic), _camera(_graphic),
      ais(_ais) {}

Bomberman::~Bomberman() {}

void Bomberman::run() {
  t = time(NULL);
  while (players.size() + ais.size() > 1) {
    graphic->run();
    bomb_actions();
    player_actions();
    if (players.size() + ais.size() <= 0)
      break ;
    ai_actions();
    bomb_actions();
    if ((time(NULL) - t) >= 10)
      add_power_up();
  }
}

void Bomberman::display_explosion(const IElement *bomb) {
  std::vector<std::pair<size_t, size_t>> coords = bomb->getCoords();
  std::vector<std::vector<IElement *>> elements = map->getMap();

  for (const auto &coord : coords) {
    if (coord.first > 0 && coord.first < elements.size() - 1 &&
        coord.second > 0 && coord.second < elements[coord.first].size() - 1 &&
        (elements[coord.first][coord.second]->getSym() == 'n' ||
         elements[coord.first][coord.second]->getSym() == 'w' ||
         elements[coord.first][coord.second]->getSym() == 'b')) {
      if (elements[coord.first][coord.second]->getSym() == 'w' ||
          elements[coord.first][coord.second]->getSym() == 'b') {
        graphic->remove(coord.first, coord.second);
      }
      map->setCase(element_creator.createExplosion(), coord.first,
                   coord.second);
      graphic->create(coord.first, coord.second, 'e');
    }
  }
}

void Bomberman::delete_explosion(const IElement *bomb) {
  std::vector<std::pair<size_t, size_t>> coords = bomb->getCoords();
  std::vector<std::vector<IElement *>> elements = map->getMap();

  for (const auto &coord : coords) {
    if (coord.first > 0 && coord.first < elements.size() - 1 &&
        coord.second > 0 && coord.second < elements[coord.first].size() - 1 &&
        (elements[coord.first][coord.second]->getSym() == 'e')) {
      graphic->remove(coord.first, coord.second);
      map->setCase(element_creator.createGround(), coord.first, coord.second);
    }
  }
}

void Bomberman::ai_actions() {
  IElement *player_case;
  std::pair<float, float> coord;
  IElement *bomb;
  int i = 0;

  for (const auto &ai : ais) {
    if ((bomb = ai->do_action(players, ais, map))) {
      bomb->setStart(time(NULL));
      bomb->addCoord(ai->getCoordBomb());
      bombs.push_back(bomb);
      map->setCase(element_creator.createBomb(), ai->getCoordBomb().first,
                   ai->getCoordBomb().second);
      graphic->create(ai->getCoordBomb().first, ai->getCoordBomb().second, 'b');
    }
    coord = ai->getCoord();
    player_case = map->getMap()[static_cast<int>(coord.first)]
                               [static_cast<int>(coord.second)];
    if (player_case->getElementType() == BONUS) {
      ai->pickBonus(player_case);
      graphic->remove(static_cast<int>(coord.first),
                      static_cast<int>(coord.second));
      map->setCase(element_creator.createGround(),
                   static_cast<int>(coord.first),
                   static_cast<int>(coord.second));
    } else if (player_case->getElementType() == OBSTACLE &&
               player_case->getObstacleType() == EXPLOSION && ai->takeDamage())
      {
	ais.erase(ais.begin() + i);
	--i;
      }
    ++i;
  }
}

void Bomberman::player_actions() {
  IElement *bomb;
  IElement *player_case;
  std::pair<float, float> coord;
  std::vector<bool> keys = graphic->getReceiver().getKeys();
  int idx = 0;

  for (const auto &player : players) {
    for (int i = 0; i != 153; i++) {
      keys = graphic->getReceiver().getKeys();
      if (keys[i] && i != 13 && (bomb = player->action(i, map))) {
        bomb->setStart(time(NULL));
        bomb->addCoord(player->getCoordBomb());
        bombs.push_back(bomb);
        map->setCase(element_creator.createBomb(), player->getCoordBomb().first,
                     player->getCoordBomb().second);
        graphic->create(player->getCoordBomb().first,
                        player->getCoordBomb().second, 'b');
      }
      if (keys[i] && i == 71)
        _camera.GameMode();
      if (keys[i] && i == 72)
        _camera.SpecMode();
      if (keys[i] && i == 27) {
        while (graphic->getDevice()->run()) {
          if (graphic->echapView() == 1)
            break;
        }
      }
    }
    coord = player->getCoord();
    player_case = map->getMap()[static_cast<int>(coord.first)]
                               [static_cast<int>(coord.second)];
    if (player_case->getElementType() == BONUS) {
      player->pickBonus(player_case);
      graphic->remove(static_cast<int>(coord.first),
                      static_cast<int>(coord.second));
      map->setCase(element_creator.createGround(),
                   static_cast<int>(coord.first),
                   static_cast<int>(coord.second));
    } else if (player_case->getElementType() == OBSTACLE &&
               player_case->getObstacleType() == EXPLOSION &&
               player->takeDamage())
      {
	players.erase(players.begin() + idx);
	--idx;
      }
    ++idx;
  }
  graphic->getReceiver().clearKeys();
}

void Bomberman::bomb_actions() {
  int i = 0;

  for (const auto &bomb : bombs) {
    if (time(NULL) - bomb->getStart() == 3 && bomb->isExploded() == false) {
      bomb->explose(map->getMap());
      display_explosion(bomb);
    } else if (time(NULL) - bomb->getStart() == 4 && bomb->isExploded()) {
      delete_explosion(bomb);
    }
    i += 1;
  }
}

void Bomberman::add_power_up() {
  std::vector<std::vector<IElement *>> m = map->getMap();
  std::random_device rd;
  std::uniform_int_distribution<int> coords_y(1, m.size() - 2);
  int y = coords_y(rd);
  std::uniform_int_distribution<int> coords_x(1, m[y].size() - 2);
  int x = coords_x(rd);
  ;

  t = time(NULL);
  while (m[y][x]->getSym() != 'n') {
    y = coords_y(rd);
    std::uniform_int_distribution<int> c(x, m[y].size() - 1);
    x = c(rd);
  }
  map->setCase(element_creator.createRandom(), y, x);
  graphic->create(y, x, 'a');
}
