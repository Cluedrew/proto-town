#include "part-ai.hpp"

// Implementation of the PartAI and the NullAI.

// NullAI ====================================================================
// Create a duplicate of a NullAI.
PartAI * NullAI::duplicate ()
{
  return new NullAI();
}

// Does nothing.
void NullAI::update (Mob & mob, sf::Time const & fr, Map & map)
{}

// TEMPERARY: This will be at the very least moved later if I keep it at all.
// FallAI has probably done its duty, so it is commented out while I make sure.
#if 0
class FallAI : public PartAI
{
private:
protected:
public:
  //FallAI () {}
  virtual ~FallAI () {}

  PartAI * duplicate ();
  /* Create a duplicate of a FallAI.
   * Return: A pointer to the copy of the FallAI, caller must free.
   * Except: May throw std::bad_alloc.
   */

  void update (Mob &, sf::Time const &, Map &);
  /* Does Noes nothing.
   * Params: A mutable reference to the parent and a constant reference to the
   *   currant frame rate.
   * Effect: Makes the mob fall down until it is on top of a non-passable tile.
   */
};
// FallAI ====================================================================
#include <iostream>
#include <SFML/Graphics.hpp>
#include "image-lib.hpp"
#include "map.hpp"
// Create a duplicate of a NullAI.
PartAI * FallAI::duplicate ()
{
  return new FallAI();
}

// Makes the mob fall down until it is on top of a non-passable tile.
void FallAI::update (Mob & mob, sf::Time const & fr, Map & map)
{
  static sf::Time fallTimer = sf::Time::Zero;
  static sf::Time fallAt = sf::milliseconds(250);

  // tileSize = 25;
  // Get the possition of the mob in tiles.
  sf::FloatRect mobBounds = mob.getBounds();
  unsigned int row = ((mobBounds.top + mobBounds.height) / tileSize) - 1;
  unsigned int col = ((mobBounds.left + mobBounds.width) / tileSize) - 1;

  // Check to see if we can fall.
  if (row < mapHeight - 1 && map.at(col, row + 1).passableEh())
  {
    fallTimer += fr;
    if (fallTimer >= fallAt)
    {
      fallTimer -= fallAt;
      moveMob(mob, 0, tileSize);
    }
  }
  else
  {
    fallTimer = sf::Time::Zero;
  }
}
#endif//if 0
