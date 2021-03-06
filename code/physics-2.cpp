#include "physics-n.hpp"

/* This is for some of the bulky calculations.
 * Usually very simple purposes, but really complicated math behind it.
 */

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "map.hpp"
#include "physics-mob.hpp"
#include "physics-tile.hpp"
#include "utils.hpp"

#include <iostream>

// Calculate a single Mob's movement across the Map.
PhysicsMob Physics::singleEntityWithWorldCore
  (PhysicsMob const & physM, sf::Time const & deltaT, Map const & map,
   bool & success)
{
  // New state of the entity if there is no collition.
  PhysicsMob newState = physM.forwardCopy(deltaT);

  // Check to see if there are any objects in the destination location.
  bool collides = false;
  {
    sf::IntRect dest = map.pixelToTileBounds(newState.getBody());
    // Does this take us out of the map?
    if (dest.top < 0 && dest.left < 0 &&
        dest.top + dest.height >= map.getMapHeight() &&
        dest.left + dest.width >= map.getMapWidth())
      collides = true;
    // Or into any impassible tiles?
    else
      collides = !isAreaEmpty(dest, map);
  }

  // If there was a collition, stop all movement.
  success = !collides;
  return (collides) ? PhysicsMob(physM.x, physM.y, physM.w,
                                 physM.h, 0, 0, 0, 0, Contact())
                    : newState;
}

// Find the next critical time.
sf::Time Physics::singleEntityNextCriticalTime
  (PhysicsMob const & physM, sf::Time const & deltaT, Map const & map)
{
  // Assume no critical times happen besides the end of the mob's movement.
  // TODO: Have a proper solution that checks mid points.
  return deltaT;
}


// see header
Contact Physics::newMobContact (PhysicsMob const & physM, Map const & map)
{
  Contact fin;

  sf::FloatRect mobBody = physM.getBody();
  sf::IntRect mobBox = map.pixelToTileBounds(mobBody);

  // The four mesurements we actually need.
  // This also high-lights the accidental duplication I have.
  float topEdge = blocksToPixels(mobBox.top);
  float leftEdge = blocksToPixels(mobBox.left);
  float rightEdge = blocksToPixels(mobBox.left + mobBox.width);
  float bottomEdge = blocksToPixels(mobBox.top + mobBox.height);

  float const within = 0.15f;

  // Top
  if (aEq(mobBody.top, topEdge, within))
  {
    for (int i = 0 ; i < mobBox.width ; ++i)
      if (!map.at(i + mobBox.left, mobBox.top - 1).passableEh())
      {
        fin.set(Contact::Top, true);
        break;
      }
  }

  // Left
  if (aEq(mobBody.left, leftEdge, within))
  {
    for (int i = 0 ; i < mobBox.height ; ++i)
      if (!map.at(mobBox.left - 1, i + mobBox.top).passableEh())
      {
        fin.set(Contact::Left, true);
        break;
      }
  }

  // Right
  if (aEq(mobBody.left + mobBody.width, rightEdge, within))
  {
    for (int i = 0 ; i < mobBox.height ; ++i)
      if (!map.at(mobBox.left + mobBox.width, i + mobBox.top).passableEh())
      {
        fin.set(Contact::Right, true);
        break;
      }
  }

  // Bottom
  if (aEq(mobBody.top + mobBody.height, bottomEdge, within))
  {
    for (int i = 0 ; i < mobBox.width ; ++i)
      if (!map.at(i + mobBox.top, mobBox.top + mobBox.height).passableEh())
      {
        fin.set(Contact::Bottom, true);
        break;
      }
  }

  return fin;
}
