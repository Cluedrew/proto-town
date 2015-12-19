#ifndef MAP_HPP
#define MAP_HPP

/* The game map handles both the grid based tiles as well as the list of mobs
 * that wander around on it. It is a real heavy weight.
 */

// Consider making it inherarit from sf::Drawable (with the tiles) so
// it can be updated cleanly.

#include <vector>
#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "tile.hpp"
class ImageLib;

extern unsigned int const mapWidth;
extern unsigned int const mapHeight;
extern unsigned int const reigonSize;

class Map : public sf::Drawable
{
private:
  // Data for the tiles.
  Grid<Tile> tiles;
protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  /* Draw the map onto a RenderTarget.
   * Params: A reference to the target of the draw operation and the
   *   RenderStates used in the operation.
   * Effect: Draws the section of the map, both tiles and ~mobs, that appears
   *   in the target's view to the target.
   * Note: Don't call directly, use target.draw(*this) instead.
   */

public:
  explicit Map (ImageLib &);
  /* Construct the map.
   * Params: The ImageLib that the Map and its contents should draw from.
   */

  virtual ~Map ();

  //Tile & at (unsigned int x, unsigned int y);
  Tile const & at (unsigned int x, unsigned int y) const;
  /* Get a reference to a tile in the map.
   * Params: The x & y coordinates of the tile in tiles. x < mapWidth and
   *   y < mapHeight.
   * Return: A constant reference to a Tile.
   * Except: Throws std::out_of_range if x or y are out of range.
   */

  int getMapWidth () const { return tiles.xSize(); }
  int getMapHeight () const { return tiles.ySize(); }
  int width () const { return tiles.xSize(); }
  int height () const { return tiles.ySize(); }
  /* Get the width or height of the map in tiles.
   * Return: An integer returning the map's width or height. These are
   *   one larger than the maximum coordinate in that axis.
   */

  /* About Pixel Vs. Tile Coordinates:
   *   Because a single pixel does not repersent a single tile the conversons
   * between pixels and tiles are not one-to-one. These functions encapsulate
   * both the translation and the type conversion for those operations.
   *   Also note that these calulations will consider there to be a plane
   * of tiles exending beyond the edge of the map, however the map does not
   * store any data on these tiles so they cannot be accessed or modified.
   */
  sf::Vector2i pixelToTile (float x, float y) const;
  sf::Vector2i pixelToTile (sf::Vector2f) const;
  /* Get the coordinates of the tile that covers the given world location.
   * Params: The pixel coordinates of a location in the world. The x & y
   *   coordinates may be given seperatly or in a Vector2.
   * Return: The tile coordinate that covers that location. Note that this
   *   tile may not exist in the map.
   */

  sf::Vector2f tileToPixel (int x, int y) const;
  sf::Vector2f tileToPixel (sf::Vector2i) const;
  /* Get the upper left hand corner of a tile.
   * Params: The coordinates of a tile. The x & y corrdinates may be given
   *   seperatly or in a Vector2.
   * Return: The pixel location of the upper left corner of the tile.
   */

  sf::Vector2f pixelModTile (float x, float y) const;
  sf::Vector2f pixelModTile (sf::Vector2f) const;
  /* Get the offset from a given location to the corner of its tile.
   * Params: The pixel coordinates of a location in the world. The x & y
   *   coordinates may be given seperatly or in a Vector2.
   * Return: The offset between the given location and the location of
   *   the upper left hand corner of the tile. Decialmal persition will
   *   lost.
   */

  // NOTE: It is working but I'm not sure it should be.
  sf::IntRect pixelToTileBounds (sf::FloatRect) const;
  /* Get the bounds of the tiles that cover a bounded region on the screen.
   * Params: The region to cover as a FloatRect and defined in pixels.
   * Return: The a IntRect repersenting the tiles nessisary to cover the
   *   given region of the screen.
   */
};

#endif//MAP_HPP
