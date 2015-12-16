#include "physics.hpp"

// Implementation of the collider functions.

#include <iostream>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "mob.hpp"
#include "map.hpp"
#include "grid.hpp"
#include "physics-mob.hpp"

// Local helper functions for collider =======================================
static sf::FloatRect getColliderPos (PhysicsMob const & cData)
{
  return sf::FloatRect(cData.x, cData.y, cData.w, cData.h);
}

// Updates the PhysicsMob for a given amount of time.
PhysicsMob Physics::incPhysicsMob (PhysicsMob const & physM,
                                   sf::Time const & time)
{
  float dt = time.asSeconds();
  return PhysicsMob(physM.x + physM.dx * dt + 0.5f * physM.ddx * dt * dt,
                    physM.y + physM.dy * dt + 0.5f * physM.ddy * dt * dt,
                    physM.w,       physM.h,
                    physM.dx * dt, physM.dy * dt,
                    physM.ddx,     physM.ddy);
}

// static bool mapCollider(Map const & map, int x, int y)
// { return map.at(xi, yi).passableEh(); }

// singleEntityWithWorld (helpers than function) =============================

/*/ Calculate a single Mob's movement across the Map.
static PhysicsMob singleEntityWithWorldCore
    (Mob const & mob, sf::Time const & fr, Map const & map)
{
  // Get the data accross (maybe the ColliderData should just be passed?).
  const PhysicsMob oldState = mob.getPhysics();

  // New state of the entity if there is no collition.
  PhysicsMob newState = {oldState.x + oldState.dx, oldState.y + oldState.dy,
      oldState.w, oldState.h, oldState.dx, oldState.dy, oldState.ddx,
      oldState.ddy};

  // Check to see if there are any objects in the destination location.
  bool collides = false;
  {
    sf::IntRect dest = map.pixelToTileBounds(getColliderPos(newState));
    if (dest.top >= 0 && dest.left >= 0 &&
        dest.top + dest.height < map.getMapHeight() &&
        dest.left + dest.width < map.getMapWidth())
      collides = true;
    else
      for (int yi = dest.top ; yi < dest.top + dest.height ; ++yi)
        for (int xi = dest.left ; xi < dest.left + dest.width ; ++xi)
          if (!map.at(xi, yi).passableEh())
            { collides = true; break; }
  }

  // If there was a collition, stop all movement.
  return (collides) ? PhysicsMob(oldState.x, oldState.y, oldState.w,
                                 oldState.h, 0, 0, 0, 0)
                    : newState;
}*/

// Calculate a single Mob's movement across the Map.
PhysicsMob Physics::singleEntityWithWorld
    (Mob const & mob, sf::Time const & fr, Map const & map)
{
  return singleEntityWithWorldCore(mob.getPhysics(), fr, map);
}
