#include "physics-mob.hpp"

// Implementation of the PhysicsMob.

#include "physics-n.hpp"
#include "accel-request.hpp"


void PhysicsMob::accelUp (AccelRequest const & request)
{
  ddy = request.proccess(dy, time);
}


void PhysicsMob::accelDown (AccelRequest const & request)
{
  ddy = -request.proccess(-dy, time);
}


void PhysicsMob::accelLeft (AccelRequest const & request)
{
  ddx = -request.proccess(-dx, time);
}


void PhysicsMob::accelRight (AccelRequest const & request)
{
  ddx = request.proccess(dx, time);
}
