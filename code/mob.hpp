#ifndef MOB_HPP
#define MOB_HPP

/* Mobs are things in the game not tied to the grid.
 * They are semi-generaic, the ai is delagated to a component (PartAI),
 * rendering is shared between all instances and physics ... WIP.
 */

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
enum class MobID : unsigned char;
#include "physics-mob.hpp"
class ImageLib;
class PartAI;
class Map;

class Mob : public sf::Drawable
{
private:
  sf::Sprite sprite;
  PartAI * ai;
  PhysicsMob phys;

protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  static PartAI * selectAI (MobID);
  /* Create the approprate AI for a mob with the given ID.
   * Params: A MobID, not exqual to cap.
   * Return: A pointer to a new PartAI, caller must free.
   * Except: [Strong] May throw std::invalid_argument or std::bag_arg.
   */

public:
  Mob (ImageLib const & imgLib, MobID id, unsigned int x, unsigned int y);
  /* Create a new mob of the given
   * Params: A constant reference to the ImageLib with the mobs texture in it,
   *   the id of the type of mob being spawned and the x and y coordinates of
   *   the mob in pixels.
   */

  virtual ~Mob ();

  void update (sf::Time const &, Map &);
  /* Move the mob one frame forward in time.
   * Params: A constant reference to the frame rate and a mutable reference to
   *   the map the mob is on.
   * Effect: Updates Mob, exact effects are dependant on the situation and the
   *   linked up PartAI.
   */

  sf::FloatRect getBounds () const;
  /* Get the bounding rectangle around the Mob.
   * Return: A FloatRect with the bounds of the mob's sprite.
   */

  sf::Vector2f getVelocity () const;
  /* Get the currant movement rate of the Mob.
   * Return: A Vector2f contaning the x and y components of the velocity.
   */

  PhysicsMob getPhysics () const;
  /* Get the currant PhysicsMob for the Mob.
   * Return: The PhysicsMob reperesenting the Mob at this moment.
   */

  friend class PartAI;
};

#endif//MOB_HPP
