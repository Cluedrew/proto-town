#ifndef PLAYER_AI_HPP
#define PLAYER_AI_HPP

/* The player mob's PartAI Component.
 */

#include <SFML/System.hpp>
#include "part-ai.hpp"

class PlayerAI : public PartAI
{
private:
    sf::Time fallTimer;
protected:
public:
  PlayerAI ();
  virtual ~PlayerAI ();

  PartAI * duplicate ();
  /* Create a duplicate of a PlayerAI.
   * Return: A pointer to the copy of the PlayerAI, caller must free.
   * Except: May throw std::bad_alloc.
   */

  void update (Mob &, sf::Time const &, Map &);
  /* Updates the player according to the situation and input.
   * Params: A mutable reference to the parent and a constant reference to the
   *   currant frame rate.
   * Effect: Makes the mob fall down until it is on top of a non-passable tile.
   */
};

#endif//PLAYER_AI_HPP
