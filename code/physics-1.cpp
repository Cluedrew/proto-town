#include "physics-n.hpp"

/* Implementation of the collider functions.
 * This file is the "dispacher" it implements most of the public functions
 * while staying away from most of more complex calculations.
 */

#include <iostream>

//#include <SFML/System/Vector2.hpp>
//#include <SFML/Graphics/Rect.hpp>
#include "mob.hpp"
#include "physics-mob.hpp"

// singleEntityWithWorld =====================================================
// Calculate a single Mob's movement across the Map.
PhysicsMob Physics::singleEntityWithWorld
    (Mob const & mob, sf::Time const & fr, Map const & map)
{
  // This will later break large movements into even smaller increments.
  return singleEntityWithWorldCore(mob.getPhysics(), fr, map);
}

