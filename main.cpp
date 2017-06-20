#include "include/AI.hpp"
#include "include/BombBonus.hpp"
#include "include/Bomberman.hpp"
#include "include/Bomberman_Map.hpp"
#include "include/BreakableObstacle.hpp"
#include "include/ConfFile.hpp"
#include "include/ExplosionObstacle.hpp"
#include "include/Graphic.hpp"
#include "include/GroundObstacle.hpp"
#include "include/Intro.hpp"
#include "include/LifeBonus.hpp"
#include "include/Menu.hpp"
#include "include/NormalBomb.hpp"
#include "include/Randmap.hpp"
#include "include/Saves.hpp"
#include "include/SpeedBonus.hpp"
#include "include/UnbreakableObstacle.hpp"
#include <map>

int main() {
  Graphic graphic;
  std::map<ConfFile::Data, std::pair<std::string, KEY_CODE>> _datas;

  graphic.getSound()->play2D("sounds/mainSound.wav", true);
  Intro intro(&graphic);
  intro.play();
  int nb_players;
  int nb_ais;
  int i;
  Menu menu(&graphic);
  if (menu.start()) {
    _datas = menu.getDatas();
    std::string tmp;
    tmp = "maps/";
    tmp += _datas[ConfFile::MAP].first;
    if (tmp == "maps/RANDOM")
      Randmap rand;
    Bomberman_Map mapGame(tmp);

    graphic.setMap(&mapGame);
    graphic.init_objects();
    graphic.display_first();
    graphic.run();
    try {
      nb_players = std::stoi(_datas.at(ConfFile::NB_PLAYERS).first);
      nb_ais = std::stoi(_datas.at(ConfFile::NB_AI).first);
    } catch (...) {
      return 0;
    }
    if (_datas[ConfFile::NB_PLAYERS].first[0] == '1')
      graphic.setFps(true);
    graphic.loadbar("assets/0_bar.png");
    graphic.init();
    std::vector<Player *> players;
    std::vector<Player *> ais;
    i = 1;
    for (int j = 0; j < nb_players; j++)
      players.push_back(new Player(&graphic, menu.getDatas(), i++));
    for (int j = 0; j < nb_ais; j++)
      ais.push_back(new AI(&graphic, i++));
    Bomberman game(players, ais, &mapGame, &graphic);
    game.run();
    graphic.gameOver();
  }
  return (0);
}
