#include "physics-n.hpp"

/* Implementation of the collider functions.
 * This file is the "dispacher" it implements most of the public functions
 * while staying away from most of more complex calculations.
 */

#include <iostream>
#include <SFML/System/Time.hpp>

#include "mob.hpp"
#include "physics-mob.hpp"
#include "accel-request.hpp"

// singleEntityWithWorld =====================================================
// Calculate a single Mob's movement across the Map.
PhysicsMob Physics::singleEntityWithWorld
    (Mob const & mob, sf::Time const & fr, Map const & map)
{
  bool success = true;
  PhysicsMob nextPhys =
      singleEntityWithWorldCore(mob.getPhysics(), fr, map, success);
  if (!success)
  {
    sf::Time halfFr = fr / 2.0f;
    nextPhys =
        singleEntityWithWorldCore(mob.getPhysics(), halfFr, map, success);
  }

  nextPhys.contact = newMobContact(nextPhys, map);
  return nextPhys;
}

/* Possible update, so I can get ride of the billion deltaT arguments.
private static field:
sf::Time Physics::deltaT;

void Physics::setFrameRate (LoopClock const & loopClock)
{
  deltaT = loopClock.getIncrement();
}

sf::Time Physics::getFrameRate ()
{
  return deltaT;
}
*/
