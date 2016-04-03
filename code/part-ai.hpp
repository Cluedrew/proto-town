#ifndef PART_AI_HPP
#define PART_AI_HPP

// There are some things with inlining and the old FallAI that
// should be addressed.

/* PartAI is the component that handles AI in mobs.
 *
 * Currantly AI is really all of the mob's behaviour. That will probably get
 * sectioned off in time, moving some of the movement and animation out and
 * leaving only the higher decition making.
 * Also PartAI is a Subclass Sandbox, providing functions for its children to
 * use in there interactions with Mob. This isn't for the classic reason of
 * isolating dependances, this is more for encapsulation as PartAI has
 * operations that Mob does not otherwise allow.
 *
 * It also defines NullAI, on of the inheriated component pieces. This one
 * does nothing.
 */

#include <SFML/System.hpp>
class Mob;
class Map;
class PhysicsMob;

class PartAI
{
private:
  // Disable copy assignment and copy constructor?
protected:
  // Subclass Sandbox:

  // Mob setters. Now with floats.
  void moveMob (Mob &, float x, float y);
  //void moveMobTo (Mob &, int x, int y);
  /* Move the mob to a different location. moveMob uses relative movement
   *   while moveMobTo uses absolute coordinates.
   * Params: A reference to the mob to be moved and the x and y offsets.
   * Effect: Changes the Mob's position.
   */

  void accelMob (Mob &, float ddx, float ddy);
  /* Accelerate the Mob, change it's velocity relavant to it currant velocity.
   * Params: A reference to the mob to be accelerated and the acceleration
   *   values in the x (ddx) and y (ddy) axis.
   * Effect: Changes the Mob's velocity.
   */

  // Might be temperary? It is a catch all for now.
  PhysicsMob & getPhysicsMob (Mob &);
  /* Get the Physics from a mob.
   * Params: Mutable reference to the Mob.
   * Return: Mutable reference to the Mob's PhysicsMob.
   */

public:
  //PartAI () {};
  virtual ~PartAI () {}

  virtual PartAI * duplicate () = 0;
  /* Create a duplicate of a PartAI.
   * Return: A pointer to the copy of the PartAI, caller must free.
   * Except: May throw std::bad_alloc.
   */

  virtual void update (Mob &, sf::Time const &, Map &) = 0;
  /* Update the parent mob.
   * Params: A mutable reference to the parent and a constant reference to the
   *   currant frame rate.
   * Effect: Dependant on override.
   */
};

class NullAI : public PartAI
{
private:
protected:
public:
  //NullAI () {}
  virtual ~NullAI () {}

  PartAI * duplicate ();
  /* Create a duplicate of a NullAI.
   * Return: A pointer to the copy of the NullAI, caller must free.
   * Except: May throw std::bad_alloc.
   */

  void update (Mob &, sf::Time const &, Map &);
  /* Does nothing.
   * Params: A mutable reference to the parent and a constant reference to the
   *   currant frame rate.
   * Effect: Does nothing.
   */
};

#include "part-ai.epp"

#endif//PART_AI_HPP
