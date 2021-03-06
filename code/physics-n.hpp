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
 *   I would like to merge these and just have physics.hpp & physics.cpp, but
 * with how much things change that might not be a good idea.
 *
 * The physics of this game works like this:
 * Tiles are locked in place and stored in the map. Although they can change
 * they don't move around. Mobs can move around and collide with tiles in the
 * map, for now they don't collide with each other to simplify calculations.
 *
 * Formally Collider. Currently it has no state.
 */

namespace sf
{
  class Time;
  template<typename T> class Rect;
}
class Mob;
class Map;
class PhysicsMob;
class PhysicsMap;
class AccelRequest;
class Contact;

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

  static Contact newMobContact (PhysicsMob const &, Map const &);
  /* Calculate the Contact data for a PhysicsMob in a Map.
   * Params: The PhysicsMob to get the Contact for and the Map it contacts.
   * Return: A new Contact object.
   */

private:
  // Helper Functions
  // Please Ignore unless you are intrested in the implementation.

  static PhysicsMob singleEntityWithWorldCore
      (PhysicsMob const &, sf::Time const &, Map const &, bool &);
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

  static bool isAreaEmpty (sf::Rect<int> const & area, Map const & map);
  static bool isAreaEmpty (int left, int top, int width, int height,
                           Map const & map);
  /* Is the entire area of the map empty?
   * Params: A Rectangle, or messurements to create a rectanglar area, and
   *   a constant reference to the Map to search.
   * Return: True if the area is entirely passable tiles, false otherwise.
   */
};


#endif//PHYSICS_N_HPP
