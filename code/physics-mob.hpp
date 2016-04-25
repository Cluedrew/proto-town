#ifndef PHYSICS_MOB_HPP
#define PHYSICS_MOB_HPP

/* Physics for a Mob:
 * A structure to repersent the physics data and properties of a entity (Mob)
 * within the game. This includes movement and collitions. Not that
 * sf::Vector2f is heavily used for pairs.
 *
 * Formally, ColliderData.
 *   Working on a struct to class conversion. That difference is mainly one of
 * style, but I think a layer of abstraction might help with this problem. It
 * may cost just a little bit of runtime speed but at this point I'm going
 * pretty slow anyways.
 */

#include <iosfwd>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include "contact.hpp"
class AccelRequest;

// Stort Cut Defines: (This file only)
#define GETPAIR(a,b) { return sf::Vector2f(a,b); }
#define SETPAIR(a,b) { this->a = a; this->b = b; }
#define GETTER(n,a,b) sf::Vector2f get ## n () GETPAIR(a,b)
#define SETTER(n,a,b) void set ## n (float a, float b) SETPAIR(a,b)
#define SETVECT(n,a,b) void set ## n (sf::Vector2f n) { a = n.x; b = n.y; }
#define GET_SET(n,a,b) GETTER(n,a,b) SETTER(n,a,b) SETVECT(n,a,b)

struct PhysicsMob
{
//private: (This will be private, but I have more changes to make first.)
  // The xy location of the entity's upper left corner. (pixels)
  float x;
  float y;
  // The width and height of the entity. (pixels)
  float w;
  float h;
  // The entity's x and y velocity. (pixels/second)
  float dx;
  float dy;
  // The entity's x and y acceleration. (pixels/second/second)
  float ddx;
  float ddy;

  // Is a given side of the entity touching a solid?
  Contact contact;

protected:
public:
  PhysicsMob (float x, float y, float w, float h,
              float dx, float dy, float ddx, float ddy,
              Contact contact = Contact()) :
    x(x), y(y), w(w), h(h), dx(dx), dy(dy), ddx(ddx), ddy(ddy),
    contact(contact)
  {}

  PhysicsMob (sf::Vector2f position, sf::Vector2f size,
              sf::Vector2f velocity, sf::Vector2f acceleration) :
    x(position.x), y(position.y), w(size.x), h(size.y),
    dx(velocity.x), dy(velocity.y), ddx(acceleration.x), ddy(acceleration.y)
  {}

  GET_SET(Position,x,y)
  GET_SET(Size,w,h)
  GET_SET(Velocity,dx,dy)
  GET_SET(Acceleration,ddx,ddy)
  /* GET_SET(NAME,X,Y)
   * Due to the number of getters and setters I macroed them.
   * These getters and setters allow you to treat the x and y component of
   * some aspect of the entity as a unit (generally a sf::Vector2f).
   * - sf::Vector2f getNAME ()
   *   return the X and Y components of NAME in a sf::Vector2f.
   * - void setNAME (float X, float Y)
   *   set the X and Y components of NAME to the parameters.
   * - void setNAME (sf::Vector2f XY)
   *   set the X and Y components of NAME to the fields of the parameter.
   */

  sf::FloatRect getBody() const
  { return sf::FloatRect(x, y, w, h); }
  /* Get the colliding body of the Mob.
   * Return: A FloatRect made from the position and size of the Mob.
   */

  void accelUp (AccelRequest const &, sf::Time const &);
  void accelDown (AccelRequest const &, sf::Time const &);
  void accelLeft (AccelRequest const &, sf::Time const &);
  void accelRight (AccelRequest const &, sf::Time const &);
  /* Change the acceleration so we are accelerating towards a particular
   *   velocity.
   * Params: An unsigned AccelRequest (all fields should be non-negative)
   *   and the time over which this acceleration will be happening.
   * Effect: Sets one of the mob's acceleration fields.
   */

  PhysicsMob forwardCopy(sf::Time const & time) const;
  /* Get a copy of what this physics mob will look like after time has passed.
   *   This does not take into account any outside factors.
   * Params: The amount of time to move the PhysicsMob forward by.
   * Return: A new PhysicsMob.
   */

  bool isOnGround() const;
  /* Check to see if the Mob is on the ground.
   * Return: True if the Mob is on any surface.
   */

#ifdef DEBUG
  void print(bool line = false) const;
  void print(std::ostream & out, bool line = false) const;
  /* Print the Physics Mob to stream, defaults to std::cout. For debugging.
   * Params: out, a mutable reference the stream to print to. If line is true
   *   then the output is followed with a newline.
   * Effect: Prints to the stream.
   * Return: Reference to the stream.
   */
#endif//DEBUG
};

// Clean up the short cuts so they don't spill.
#undef GET_SET
#undef SETVECT
#undef SETTER
#undef GETTER
#undef SETPAIR
#undef GETPAIR

#ifdef DEBUG
std::ostream & operator<< (std::ostream & out, PhysicsMob const & physMob);
#endif//DEBUG

#endif//PHYSICS_MOB_HPP
