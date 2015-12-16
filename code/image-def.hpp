#ifndef IMAGE_DEF_HPP
#define IMAGE_DEF_HPP

/* The enumerations used by the ImageLib to select different sprites within
 * one of the loaded textures, see below for exactly how.
 * 
 * These were taken out for purposes of readablity and because it will likely
 * be updated far more than the ImageLib itself, hence there might be some
 * dependances saved. Hence, avoid including this in header files.
 * 
 * Originally there was room for 400 tiles in the raw image. I realized that
 * was excesive so I stopped all the enum at 255. If I run out I can just
 * change the type here and in the forward declaration in image-lib.hpp but
 * really this project shouldn't get that big. It might but I doubt it.
 * 
 * All the enum have a value ::cap that is there last value. It is their null
 * value and can be used as the upper (exclusive) limit on loops.
 * 
 * TileID: Counts (1*tileSize) by (1*tileSize) squares, left to right top to
 * bottom. Each row contains exactly 20 tiles. Maybe I shouldn't hard code
 * that but for the scope of this project it will work.
 * 
 * MobID & MobStateID: Gives out (1*tileSize) by (2*tileSize) rectangles.
 * MobID is the row (all images of the same mob are in the same row) and
 * MobStateID is the column. Hence it works sort of like a look up table.
 */

// The side length of a drawn tile.
// This is used in defining the sizes of a lot of mobs as well.
extern unsigned int const tileSize;

// Enumeration of map tile images.
enum class TileID : unsigned char
{
  edge,
  blueSky,
  grass,
  dirt,
  cap
};

// Enumeration of the mob images.
enum class MobID : unsigned char
{
  player,
  cap
};

// Enumeration of the mob states.
enum class MobStateID : unsigned char
{
  standing,
  cap
};

#endif//IMAGE_DEF_HPP
