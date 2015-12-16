#include "image-lib.hpp"

// Implementation for the image library, which holds textures.

#include <cstdlib>
#include <string>
#include <stdexcept>
#include "image-def.hpp"

// Value for the side length of a drawn tile.
unsigned int const tileSize = 25;

// The number of tiles in each row of the "inkv7tiles" file.
// REMEMBER: If this is changed the image file has to change too.
static unsigned int const tilesByRow = 20;

static std::string loadError("ImageLib: runtime_error on loadFromFile");

// Constructors and Deconstructor ============================================
ImageLib::ImageLib () :
  mapTiles(), mobImages()
{
  if (!(mapTiles.loadFromFile("resources/inkv7tiles.png") &&
      mobImages.loadFromFile("resources/inkv7mobs.png")))
  {
    // error on loadFromFile, I don't have any recovery for this, in fact I
    // used to just quit, but now I have a labeling exception.
    throw std::runtime_error(loadError);
  }
}

ImageLib::~ImageLib ()
{}

// Implementation Functions ==================================================
// Get the sprite sheet for tiles.
sf::Texture const & ImageLib::GetTileTex () const
{
  return mapTiles;
}

// Get the sprite sheet for mobs.
sf::Texture const & ImageLib::GetMobTex () const
{
  return mobImages;
}

// Calculate the rectangle that outlines a given tile's sprite.
sf::IntRect ImageLib::GetTileRect (TileID id) const
{
  return sf::IntRect((int(id) % tilesByRow) * tileSize,
                     (int(id) / tilesByRow) * tileSize,
                     tileSize, tileSize);
}

// Calculate the rectangle that outline a given mob in a given state.
sf::IntRect ImageLib::GetMobRect (MobID mid, MobStateID sid) const
{
  return sf::IntRect(int(sid) * tileSize, int(mid) * 2 * tileSize,
                     tileSize, 2 * tileSize);
}

/*   This class was (is actually, but I hope to change it soon) a singleton.
 * Although this is not a good thing I did do one cool thing, which is it was
 * an "inheritable singleton". In theroy, never got to try it, this would
 * allow one instance of it or any of its child classes to exist. I did this
 * with the usual private instance field (pointer to instance or NULL) and
 * public GetInstance function, actually it was a little different, it
 * created a new instance if there was none but it didn't save it. Instead
 * the protected constructor saved the new object to the instance field and
 * requested DestroyInstance be called on exit.
 *   The idea is to let it be inherited and be the constructor can be called
 * by the child classes, each having there own GetInstance function. But there
 * are a few problems, branches in the hierarcy and lack of enforcement to
 * name a few.
 */
