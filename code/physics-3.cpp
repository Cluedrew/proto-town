#include "physics-n.hpp"

// Small(er) calculations and helpers.

#include <cmath>
#include "accel-request.hpp"

// Updates the PhysicsMob for a given amount of time.
PhysicsMob Physics::incPhysicsMob (PhysicsMob const & physM,
                                   sf::Time const & time)
{
  float dt = time.asSeconds();
  return PhysicsMob(physM.x + physM.dx * dt + 0.5f * physM.ddx * dt * dt,
                    physM.y + physM.dy * dt + 0.5f * physM.ddy * dt * dt,
                    physM.w, physM.h,
                    physM.dx + physM.ddx * dt, physM.dy + physM.ddy * dt,
                    physM.ddx, physM.ddy);
}

// Find the amount of time it will take physM to move dist. Return the minimum
// of that time and maxTime. 'v' is some axis, signs are considered.
sf::Time Physics::timeToMove (PhysicsMob const & physM,
                              float dv, float ddv,
                              sf::Time const & maxTime,
                              float dist)
{
  // Special cases that check for 0s.
  if (sf::Time::Zero == maxTime || 0f == dist)
    return sf::Time::Zero
  else if (0f == dv && 0f == ddv)
    return maxTime;

  // To simplify the following calculations we will consider dist as forward
  // in all cases.
  if (dist < 0)
  {
    dist = -dist;
    ddv = -ddv;
    dv = -dv;
  }

  // If acceration is forward or zero will a forward velocity, dist will be
  // traveled eventually.
  if (0 < ddv || (0 == ddv && 0 < dv))
  {
    // Find travel time
    // Quadratic Formula: x = (-b -+ (b*b-4 * a * c)^(1/2)) / (2 * a)
    double determanint = (dv * dv) - (4.0 * ddv * dist);
    double detRoot = sqrt(determaint);
    // Because ddv
    sf::Time travelTime =
    return (travelTime < maxTime) ? travelTime : maxTime;
  }
  // If acceration and velocity is backwards it will take infinate time.
  else if (ddv < 0 && dv < 0)
    return maxTime;
  // Otherwise, velocity might cross dist before accerating way.
  else
  {
    // We have to check the determanint.
    double determanint = (dv * dv) - (4.0 * ddv * dist);
    // No real roots, dist is never traveled.
    if (determanint < 0)
    {}
    // One real root, return it if it is lower than maxTime.
    else if (0 == determanint)
    {
      sf::Time const & travelTime = sf::seconds(-dv / (2 * ddv));
      return (travelTime < maxTime) ? travelTime : maxTime;
    }
    // Two real roots, find the smaller of possitive ones.
    else
    {}
  }
}
