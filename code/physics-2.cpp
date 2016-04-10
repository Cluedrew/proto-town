#include "physics-n.hpp"

/* This is for some of the bulky calculations.
 * Usually very simple purposes, but really complicated math behind it.
 */

#include <SFML/System/Time.hpp>
#include "map.hpp"
#include "physics-mob.hpp"
#include "physics-tile.hpp"

// Calculate a single Mob's movement across the Map.
PhysicsMob Physics::singleEntityWithWorldCore
  (PhysicsMob const & physM, sf::Time const & deltaT, Map const & map)
{
  // New state of the entity if there is no collition.
  PhysicsMob newState = physM.forwardCopy(deltaT);
      /*/ If the above continues to work, remove the below.
     {physM.x + physM.dx, physM.y + physM.dy,
      physM.w, physM.h,
      physM.dx + physM.ddx, physM.dy + physM.ddy,
      physM.ddx, physM.ddy};
      //*/
  //physM.print(true);
  //newState.print(true);


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

// Find the next critical time.
sf::Time Physics::singleEntityNextCriticalTime
  (PhysicsMob const & physM, sf::Time const & deltaT, Map const & map)
{
  // Assume no critical times happen besides the end of the mob's movement.
  // TODO: Have a proper solution that checks mid points.
  return deltaT;
}
