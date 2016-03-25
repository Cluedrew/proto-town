#ifndef ACCEL_REQUEST_HPP
#define ACCEL_REQUEST_HPP

// Stucture that has the data for accelerating towards a velocity.
// Part of the physics engine.


struct AccelRequest
{
  float targetVelocity;
  // The velocity that the acceration should bring the object closer to.
  // pixels/second

  float maxIncrease;
  // The max increase in velocity (upper bound on acceleration).
  // pixels/second/second

  float maxDecrease;
  // The max decrease in velocity (lower bound on acceleration).
  // pixels/second/second

  AccelRequest (float tv, float maxIn, float maxDe);
  /* Define an accelation request.
   * Params: All messurments are directionless and should be positive.
   */

  float process (float currentVelocity, sf::Time const & over) const;
  /* Process the request, by fining an acceleration that brings the
   *   currentVelocity towards the targetVelocity, without going outside
   *   the range [-maxDecrease, maxIncrease].
   * Params: The currentVelocity, and the amount of time over which
   *   the acceleration should take place.
   * Return: The resulting acceleration.
   */
};
/* This structure is used as an argument in several functions that create
 * smooth acceleration. Generally creating a constant for a type of movement
 * and passing a reference to it should work fine.
 *
 * targetVelocity is the speed (that is the magnatude) that the object would
 * like to move at. maxIncrease & maxDecrease are the highest and lowest
 * accelerations it will undergo. Most of the time one of these will be
 * the acceleration, except when the currant speed is really close to the
 * target speed, where it will be in the middle so that the target is
 * reached at the end of the frame.
 *
 * Time and direction data comes from the particular function.
 */

#endif//ACCEL_REQUEST_HPP
