#ifndef	AI_HPP_
# define AI_HPP_

#include "Player.hpp"

class	AI : public Player
{
public:
  AI(Graphic *graphic, const int & _nb_team);
  const bool            down(const std::vector<std::vector<IElement *>> & map);
  const bool            up(const std::vector<std::vector<IElement *>> & map);
  const bool            left(const std::vector<std::vector<IElement *>> & map);
  const bool            right(const std::vector<std::vector<IElement *>> & map);
  const bool            isBombUp(const std::vector<std::vector<IElement *>> & map) const;
  const bool            isBombDown(const std::vector<std::vector<IElement *>> & map) const;
  const bool            isBombLeft(const std::vector<std::vector<IElement *>> & map) const;
  const bool            isBombRight(const std::vector<std::vector<IElement *>> & map) const;
  const bool            escapeBomb(const std::vector<std::vector<IElement *>> & map);
  const bool            forward(const std::vector<std::vector<IElement *>> & map, int _dir);
  virtual IElement		*do_action(const std::vector<Player *> & players, const std::vector<Player *> & ai, const Bomberman_Map *map);
  IElement		*aggressiveAction(const std::vector<Player *> & players, const std::vector<Player *> & ai, const Bomberman_Map *map);
  IElement		*fugitiveAction(const std::vector<Player *> & players, const std::vector<Player *> & ai, const Bomberman_Map *map);
  const float		getDistanceWith(Player * players) const;
  const bool		isBreakableBlock(const std::vector<std::vector<IElement *>> & map) const;
  const bool          possibleToMove(const std::vector<std::vector<IElement *>> & map) const;
};

#endif /* !AI_HPP_ */
