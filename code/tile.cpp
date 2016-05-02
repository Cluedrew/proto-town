#include "tile.hpp"

// Implementation of the map tile.

#include "image-lib.hpp"
#include "image-def.hpp"

// Constructors and Deconstructor ============================================
Tile::Tile () :
  x(0), y(0), background(), foreground(), passable(false)
{}


Tile::~Tile ()
{}

// Operator Overloads ========================================================
/*Tile & Tile::operator= (Tile const & other)
{
  x = other.x;
  y = other.y;
  background = other.background;
  return *this;
}*/

// Implementation Functions ==================================================
void Tile::init(unsigned int x_, unsigned int y_, TileID background_,
                ImageLib & lib)
{
  // check... so now I forget what is supposed to be checked...
  x = x_;
  y = y_;
  background.setTexture(lib.GetTileTex());
  background.setTextureRect(lib.GetTileRect(background_));
  background.setPosition(x * tileSize, y * tileSize);
  if (TileID::edge == background_)
    passable = false;
  else
    passable = true;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // The background goes on first, so it is in the back.
  target.draw(background, states);

  // Foreground, back to front.
  for (std::vector<sf::Sprite>::const_iterator it = foreground.cbegin() ;
       it != foreground.end() ; ++it)
  {
    target.draw(*it, states);
  }
}

// Check to see if the tile is passable.
bool Tile::passableEh () const
{
  return passable && foreground.empty();
}

// see header
void Tile::pushForeground(TileID foreground_, ImageLib & lib)
{
  foreground.emplace_back(lib.GetTileTex(), lib.GetTileRect(foreground_));
  foreground.back().setPosition(x * tileSize, y * tileSize);
}

// see header
void Tile::cullForeground()
{
  foreground.pop_back();
}
