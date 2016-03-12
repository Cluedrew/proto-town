#ifndef PHYSICS_N_HPP
#define PHYSICS_N_HPP

/* Pure static class that encapsulates the physics (kinamatics and collitions)
 * calculations for objects in the game world. Data for the physics of a class
 * X is encapsulated in the PhysicsX structure.
 *
 * Implemented by the numbered physics files. Which may be excessive but it
 * this is my first time writing this complex of physics anything so it helps
 * me sort it out in my head.
 * 1: Public Functions, dispatchers for the other files.
 * 2: Some of the really big calculation functions.
 * 3: Small helper calculator functions.
 *
 * The physics of this game works like this:
 * Tiles are locked in place and stored in the map. Although they can change
 * they don't move around. Mobs can move around and collide with tiles in the
 * map, for now they don't collide with each other to simplify calculations.
 *
 * Formally Collider. Currently it has no state.
 */

#include <SFML/System/Time.hpp>
class Mob;
class Map;
class PhysicsMob;
class PhysicsMap;

struct Physics
{
  static PhysicsMob singleEntityWithWorld
      (Mob const &, sf::Time const &, Map const &);
  /* Calculate a single Mob's movement across the Map.
   * Params: A reference to a Mob repersenting the entity, the time to move
   *   foward by and a reference to the Map repersenting the world.
   * Return: A PhysicsMob showing the new state of the entity after the
   *   given time has passed.
   */

  static PhysicsMob incPhysicsMob (PhysicsMob const &, sf::Time const &);
  /* Move a PhysicsMob forward in time assuming no colitions.
   * Params: The PhysicsMob to increment and the amount of time to move it
   *   forward by.
   * Return: A new PhysicsMob with possition and velocity updated.
   */

  // Stucture that has the data for accelerating towards a velocity.
  struct AccelRequest
  {
    AccelRequest (float tv, float maxIn, float maxDe) :
      targetVelocity(tv), maxIncrease(maxIn), maxDecrease(maxDe)
    {}
    /* Define an accelation request.
     * Params: All messurments are directionless and should be possitive.
     */

    float targetVelocity;
    // The velocity that the acceration should bring the object closer to.

    float maxIncrease;
    // The max increase in velocity (upper bound on acceleration).

    float maxDecrease;
    // The max decrease in velocity (lower bound on acceleration).
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

  static float accelTowardsRight
      (PhysicsMob const &, sf::Time const &, AccelRequest const &);
  static float accelTowardsLeft
      (PhysicsMob const &, sf::Time const &, AccelRequest const &);
  static float accelTowardsDown
      (PhysicsMob const &, sf::Time const &, AccelRequest const &);
  static float accelTowardsUp
      (PhysicsMob const &, sf::Time const &, AccelRequest const &);
  /* Accel* function calculate smooth acceleration. WIP
   */

  static void updateMobContact (PhysicsMob &, Map const &);
  // Modifer version?

  static Contact newMobContact (PhysicsMob const &, Map const &);
  /*
   * Params: The PhysicsMob to get the Contact for and the Map it contacts.
   * Return: A new Contact object.
   */

private:
  // Helper Functions
  // Please Ignore unless you are intrested in the implementation.

  static PhysicsMob singleEntityWithWorldCore
      (PhysicsMob const &, sf::Time const &, Map const &);
  /* Increment a Mob's movement across the Map over Time.
   *   Note that this is for very small, 'safe' amounts of movement.
   * Params:
   * Return:
   */

  static sf::Time singleEntityNextCriticalTime
      (PhysicsMob const & physM, sf::Time const & deltaT, Map const & map);
  /* Find the next critical time.
   * Params:
   * Return:
   */

  static float accelTowardsAxis
      (float dv, sf::Time const & deltaT, AccelRequest request);
  /* Return acceleration along an axis.
   * Params:
   *   dz: Current velocity along axis.
   *   deltaT: Change in time.
   *   request: Signed request for change in acceleration.
   * Return: The new acceleration along the axis.
   */
};

template<typename T>
T medianOfThree (T val1, T val2, T val3);
/* Return the midian of the three provided values.
 * Requires bool operator< (T, T) to be defined.
 * Params: Three values of a type that is orderable by operator<.
 * Return: One of the three values, the middle one in ordering.
 */

#endif//PHYSICS_N_HPP
