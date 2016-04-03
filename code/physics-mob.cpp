#include "physics-mob.hpp"

// Implementation of the PhysicsMob.

#include "physics-n.hpp"
#include "accel-request.hpp"

#include <iostream>


void PhysicsMob::accelUp (AccelRequest const & request, sf::Time const & dt)
{
  ddy = -request.process(-dy, dt);
}


void PhysicsMob::accelDown (AccelRequest const & request, sf::Time const & dt)
{
  ddy = request.process(dy, dt);
}


void PhysicsMob::accelLeft (AccelRequest const & request, sf::Time const & dt)
{
  ddx = -request.process(-dx, dt);
}


void PhysicsMob::accelRight (AccelRequest const & request, sf::Time const & dt)
{
  ddx = request.process(dx, dt);
}
