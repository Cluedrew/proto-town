#include "physics-n.hpp"

/* Implementation of the collider functions.
 * This file is the "dispacher" it implements most of the public functions
 * while staying away from most of more complex calculations.
 */

#include <iostream>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "mob.hpp"
#include "map.hpp"
#include "grid.hpp"
#include "physics-mob.hpp"

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

// singleEntityWithWorld =====================================================
// Calculate a single Mob's movement across the Map.
PhysicsMob Physics::singleEntityWithWorld
    (Mob const & mob, sf::Time const & fr, Map const & map)
{
  // This will later break large movements into even smaller increments.
  return singleEntityWithWorldCore(mob.getPhysics(), fr, map);
}
