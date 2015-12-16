#ifndef IMAGE_LIB_HPP
#define IMAGE_LIB_HPP

/* The image library holds all of the textures needed by the game in one place
 * and handles there allocation, deallocation and finding the subsections of
 * them needed for sprites.
 * 
 * Its main feature is the ImageLib class, which is a singleton that holds all
 * of that data. (Yes singletons are overused, but I think this is one of the
 * correct times to use it.) Also included are some relivant definifions. The
 * side length of a tile in pixels is one (tileSize). There are the three ID
 * enumerations used to get subsections of the main sprite sheets for drawing.
 * 
 * About the images the textures are loaded from:
 * inkv7tiles.png: Divided into 25x25 pixel images of tiles. Tiles are drawn
 *   on a grid by the map, in fact they include all such images.
 * inkv7mobs.png: Divided onto 25x50 (twice as tall as wide) images of mobs in
 *   various states. Mobs are not locked to the grid and usually reperesnt
 *   characters. Each row is dedicated to a mob and each column is dedicated
 *   to a state.
 */

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

// The side length of a drawn tile.
extern unsigned int const tileSize;

// Enumeration of map tile images.
enum class TileID : unsigned char;

// Enumeration of the mob images.
enum class MobID : unsigned char;

// Enumeration of the mob states.
enum class MobStateID : unsigned char;

class ImageLib
{
private:
  // 1x1 (times tile size) squares used as tiles in the map.
  sf::Texture mapTiles;
  // 2x1 rectangles used as sprites for mobs.
  sf::Texture mobImages;
protected:
public:
  ImageLib ();
  /* Set up the ImageLib, loading all textures.
   * Except: [Strong] Throws std::runtime_error if images can't be loaded.
   */
  
  virtual ~ImageLib ();
  
  sf::Texture const & GetTileTex () const;
  /* Get the sprite sheet for tiles.
   * Return: A constaint reference to the tile sprite sheet's texture.
   */
  
  sf::Texture const & GetMobTex () const;
  /* Get the sprite sheet for mobs.
   * Return: A constaint reference to the mob sprite sheet's texture.
   */
  
  sf::IntRect GetTileRect (TileID) const;
  /* Calculate the rectangle that outlines a given tile's sprite.
   * Params: The TileID for the tile in question.
   * Return: A IntRect with the location and size of the tile.
   */
  
  sf::IntRect GetMobRect (MobID, MobStateID) const;
  /* Calculate the rectangle that outline a given mob in a given state.
   * Params: The MobID for the requested mob and the MobStateID for its
   *   requested state.
   * Return: An IntRect with the location and size of the mob.
   */
};

#endif//IMAGE_LIB_HPP
