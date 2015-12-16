#ifndef TILE_HPP
#define TILE_HPP

/* A tile on the map,
 */

#include <SFML/Graphics.hpp>
enum class TileID : unsigned char;
class ImageLib;

class Tile : public sf::Drawable
{
private:
  // The tile's location on the map.
  unsigned int x;
  unsigned int y;

  // The sprite that repersents the background of the tile.
  sf::Sprite background;

  // Is the tile passable or not?
  bool passable;
protected:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
  Tile ();
  /* Create a new empty tile.
   */

  virtual ~Tile ();

  //Tile & operator= (Tile const &);

  void init(unsigned int x, unsigned int y, TileID background, ImageLib& lib);
  /* Initalize the tile, tiles should always be initalized before use.
   * Params: x & y are the coordinates of the tile on the map. background is
   *   the id of the tile's background image and lib is an ImageLib to get
   *   that from.
   * Effect: Initalizes the tile, setting up all fields.
   */

  bool passableEh () const;
  /* Check to see if the tile is passable.
   * Return: True if the tile is passable, false if it is 'solid'.
   */
};

#endif//TILE_HPP
