#ifndef PHYSICS_MOB_HPP
#define PHYSICS_MOB_HPP

/* Physics for a Mob:
 * A structure to repersent the physics data and properties of a entity (Mob)
 * within the game. This includes movement and collitions. Not that
 * sf::Vector2f is heavily used for pairs.
 *
 * Formally, ColliderData.
 */

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

// Stort Cut Defines: (This file only)
#define GETPAIR(a,b) { return sf::Vector2f(a,b); }
#define SETPAIR(a,b) { this->a = a; this->b = b; }
#define GETTER(n,a,b) sf::Vector2f get ## n () GETPAIR(a,b)
#define SETTER(n,a,b) void set ## n (float a, float b) SETPAIR(a,b)
#define SETVECT(n,a,b) void set ## n (sf::Vector2f n) { a = n.x; b = n.y; }
#define GET_SET(n,a,b) GETTER(n,a,b) SETTER(n,a,b) SETVECT(n,a,b)

struct PhysicsMob
{
  PhysicsMob (float x, float y, float w, float h,
              float dx, float dy, float ddx, float ddy) :
    x(x), y(y), w(w), h(h), dx(dx), dy(dy), ddx(ddx), ddy(ddy)
  {}

  PhysicsMob (sf::Vector2f position, sf::Vector2f size,
              sf::Vector2f velocity, sf::Vector2f acceleration) :
    x(position.x), y(position.y), w(size.x), h(size.y),
    dx(velocity.x), dy(velocity.y), ddx(acceleration.x), ddy(acceleration.y)
  {}

  // The xy location of the entity's upper left corner.
  float x;
  float y;
  // The width and height of the entity.
  float w;
  float h;
  // The entity's x and y velocity. (pixels/second)
  float dx;
  float dy;
  // The entity's x and y acceleration. (pixels/second/second)
  float ddx;
  float ddy;

  // Is a given side of the entity touching a solid?
  // EXPERAMENTAL
  //enum Side {Left, Top, Right, Bottem};
  //bool contact[4];

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
};

// Clean up the short cuts so they don't spill.
#undef GET_SET
#undef SETVECT
#undef SETTER
#undef GETTER
#undef SETPAIR
#undef GETPAIR

#endif//PHYSICS_MOB_HPP
