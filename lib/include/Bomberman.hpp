#ifndef	BOMBERMAN_HPP_
# define BOMBERMAN_HPP_

#include <ctime>
#include "MyEventReceiver.hpp"
#include "IElement.hpp"
#include "CreateElement.hpp"
#include "Graphic.hpp"
#include "Bomberman_Map.hpp"
#include "Player_graphic.hpp"

class	Bomberman
{
public:
  Bomberman(std::vector<IElement *> _players, Bomberman_Map *map, Graphic *_graphic);
  ~Bomberman();

  int	run();
  int	player_actions();
  int	bomb_actions();
  void	add_power_up();
  void  display_explosion(IElement *bomb);
  void  delete_explosion(IElement *bomb);

private:
  std::vector<IElement *>	players;
  std::vector<IElement *>	bombs;
  std::vector<Player_graphic *>	players_graphic;
  Bomberman_Map			*map;
  time_t			t;
  Graphic			*graphic;
  CreateElement			element_creator;
};

#endif /* BOMBERMAN_HPP_ */
