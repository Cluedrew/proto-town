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
   * TODO: Add suport for the contact array.
   */

  static PhysicsMob incPhysicsMob (PhysicsMob const &, sf::Time const &);
  /*
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
  }
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

  static float AccelTowardsRight
      (PhysicsMob const &, sf::Time const &, AccelRequest const &);
  static float AccelTowardsLeft
      (PhysicsMob const &, sf::Time const &, AccelRequest const &);
  static float AccelTowardsDown
      (PhysicsMob const &, sf::Time const &, AccelRequest const &);
  static float AccelTowardsUp
      (PhysicsMob const &, sf::Time const &, AccelRequest const &);
  /* Accel* function calculate smooth acceleration. WIP
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

  static sf::Time Physics::singleEntityNextCriticalTime
      (PhysicsMob const & physM, sf::Time const & deltaT, Map const & map);
  /* Find the next critical time.
   */

  static float AccelTowardsAxis
      (float, sf::Time const &, AccelRequest const &);
};

#endif//PHYSICS_N_HPP
