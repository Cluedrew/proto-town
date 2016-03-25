#include "accel-request.hpp"


AccelRequest (float tv, float maxIn, float maxDe) :
  targetVelocity(tv), maxIncrease(maxIn), maxDecrease(maxDe)
{}


// T may be any orderable type with operator< (T, T) defined.
// Cap val so it is between min & max.
template<typename T>
static T minMaxCap (T min, T val, T max)
{
  //assert(min < max);

  if (max < val) {
    return max;
  } else if (val < min) {
    return min;
  } else {
    return val;
  }
}


float AccelRequest::process
    (float currentVelocity, sf::Time const & over) const
{
  // Get the acceleration to arrive at the target velocity.
  float accelToTarget = (targetVelocity - currentVelocity) / over;

  // Get the center of the three (so the maxes act as limits).
  return minMaxCap<float>(-maxDecrease, accelToTarget, maxIncrease);
}
