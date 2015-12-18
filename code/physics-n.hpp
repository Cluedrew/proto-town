#ifndef PHYSICS_N_HPP
#define PHYSICS_N_HPP

/* Pure static class that encapsulates the physics (kinamatics and collitions)
 * calculations for objects in the game world. Data for the physics of a class
 * X is encapsulated in the PhysicsX structure. Implemented by the numbered
 * physics files.
 *
 * The physics of this game works like this:
 * Tiles are locked in place and stored in the map. Although they can change
 * they don't move around. Mobs can move around and collide with tiles in the
 * map, for now they don't collide with each other to simplify calculations.
 *
 * Formally Collider. Currently it has no state.
 */

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
class Mob;
class Map;
class PhysicsMob;

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

  //static PhysicsTile const & getTilePhysics (Map const &, int x, int y);
  /*
   */
  //static PhysicsTile voidTilePhysics;
private:
  // Helper functions
  static PhysicsMob singleEntityWithWorldCore
      (PhysicsMob const &, sf::Time const &, Map const &);
};

#endif//PHYSICS_N_HPP
