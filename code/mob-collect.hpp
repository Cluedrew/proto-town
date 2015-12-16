#ifndef MOB_COLLECT_HPP
#define MOB_COLLECT_HPP

/* A collection of mobs, storage for the mobs but also creation and memory
 * management.
 */

#include <vector>
#include <SFML/Graphics.hpp>
#include "mob.hpp"
class ImageLib;
class Map;

class MobCollect : public sf::Drawable
{
private:
  ImageLib const & imgLib;
  std::vector<Mob> mobs;
protected:
  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Draws the mobs to the target.
   */

public:
  explicit MobCollect (ImageLib const &);
  /* Create a new collection of mobs.
   * Params: A reference to an single ImageLib to draw the images for the
   *   Mob's Sprites from.
   */

  virtual ~MobCollect ();

  void spawn (MobID id, unsigned int x, unsigned int y);
  /* Spawn a new mob and add it to the collection.
   * Params: The id of the type of mob being spawned and its x and y
   *   coordinates of the mob in pixels.
   */

  void update (sf::Time const &, Map &);
  /* Send the update command to all of the mobs in the collection.
   * Params: A constant reference to the framerate and a mutable reference
   *   to the map the mobs in the collection are on.
   * Effect: All mobs in the collection are updated one frame.
   */
};

#endif//MOB_COLLECT_HPP
