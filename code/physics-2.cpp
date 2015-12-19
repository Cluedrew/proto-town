#include "physics-2.hpp"

/* This file implements all of the 'internal' aspects of the Physics class.
 * Because they are not to be used externally and have no header documentation
 * there is a mini-header here you can look at.
 *
 * Most things here are only to be used as helper functions for something in
 * physics.cpp, the only reason it is in the header at all is A) it is good
 * form and B) makes it easier to change if some exception to the rule comes
 * up.
 *
 * These functions are the ones that do most of the number crunching, they
 * don't interact with other parts of the system in any real way. Could have
 * gotten away with one file but two seems nice.
 */

//PhysicsMob Physics::singleEntityWithWorldCore
//  (PhysicsMob const & physM, sf::Time const & deltaT, Map const & map);
/* Increment a Mob's movement across the Map over Time.
 *   Note that this is for very small, 'safe' amounts of movement.
 * Params:
 * Return:
 */

// ===========================================================================
// Implementation ============================================================
// ===========================================================================

#include "map.hpp"
#include "physics-mob.hpp"
#include "physics-tile.hpp"

// Calculate a single Mob's movement across the Map.
PhysicsMob Physics::singleEntityWithWorldCore
  (PhysicsMob const & physM, sf::Time const & deltaT, Map const & map)
{
  // New state of the entity if there is no collition.
  PhysicsMob newState = {physM.x + physM.dx, physM.y + physM.dy,
      physM.w, physM.h, physM.dx, physM.dy, physM.ddx,
      physM.ddy};

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
      for (int yi = dest.top ; yi < dest.top + dest.height ; ++yi)
        for (int xi = dest.left ; xi < dest.left + dest.width ; ++xi)
          if (!map.at(xi, yi).passableEh())
            { collides = true; break; }
  }

  // If there was a collition, stop all movement.
  return (collides) ? PhysicsMob(physM.x, physM.y, physM.w,
                                 physM.h, 0, 0, 0, 0)
                    : newState;
}

// Find the next crittical time.
sf::Time Physics::singleEntityNextCriticalTime
  (PhysicsMob const & physM, sf::Time const & deltaT, Map const & map)
{
  // Assume no critical times happen besides the end of the mob's movement.
  return deltaT;
}
