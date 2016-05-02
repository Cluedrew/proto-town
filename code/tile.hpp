#ifndef TILE_HPP
#define TILE_HPP

/* A tile on the map,
 */

#include <vector>
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

  // Sprites in the foreground of the tile.
  // Foreground objects are all the same so there is no additional data.
  std::vector<sf::Sprite> foreground;

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

  void pushForeground(TileID foreground_, ImageLib & lib);
  /* Push the object repersented by TileID into the foreground of the Tile.
   * Params: The id of the Tile that repersints the object and the lib to
   *   draw the sprite from.
   * Effect: Adds an object to the forground. May dhange if the Tile is
   *   passable or not.
   */

  void cullForeground();
  /* Remove the foremost object from the Tile's foreground.
   *   There must be at least one object in the forground.
   * Effect: Removes an object from the foreground. May change if the Tile
   *   is passable or not.
   */
};

#endif//TILE_HPP
