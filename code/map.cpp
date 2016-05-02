#include "map.hpp"

// Implementation of the game map.

#include "image-def.hpp"

unsigned int const mapWidth = 30;
unsigned int const mapHeight = 20;
unsigned int const reigonSize = 10;

// Constructors and Deconstructor ============================================
Map::Map (ImageLib & lib) :
  tiles(mapWidth, mapHeight/*, reigonSize, reigonSize*/)
{
  for (unsigned int y = 0 ; y < mapHeight ; ++y)
  {
    for (unsigned int x = 0 ; x < mapWidth ; ++x)
    {
      if (0 == y || 0 == x || mapHeight - 1 == y || mapWidth - 1 == x)
        tiles.at(x, y).init(x, y, TileID::edge, lib);
      else if (10 > y)
        tiles.at(x, y).init(x, y, TileID::blueSky, lib);
      else if (10 < y)
      {
        tiles.at(x, y).init(x, y, TileID::dirt, lib);
        //if (x < 20)
        //  tiles.at(x, y).pushForeground(TileID::dirtFG, lib);
      }
      else // (10 == y)
      {
        tiles.at(x, y).init(x, y, TileID::grass, lib);
        //if (x < 20)
        //  tiles.at(x, y).pushForeground(TileID::grassFG, lib);
      }
    }
  }
}

Map::~Map ()
{}

// Implementation Functions ==================================================
// Draw the map onto a RenderTarget.
void Map::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
  // Something to bound the edges of the drawn area might help.

  // Drawing: First the tiles and then the entites.
  // Quick Test loops.
  for (unsigned int y = 0 ; y < mapHeight ; ++y)
  {
    for (unsigned int x = 0 ; x < mapWidth ; ++x)
      target.draw(tiles.at(x,y));
  }
}

// Getters and Setters -------------------------------------------------------
// Get a reference to a tile in the map.
Tile const & Map::at (unsigned int x, unsigned int y) const
{
  return tiles.at(x, y);
}

// Coordinate Calculations ---------------------------------------------------
// Get the coordinates of the tile that covers the given world location.
sf::Vector2i Map::pixelToTile (float x, float y) const
{
  return sf::Vector2i((int)x / tileSize, (int)y / tileSize);
}
sf::Vector2i Map::pixelToTile (sf::Vector2f coords) const
{ return pixelToTile(coords.x, coords.y); }

// Get the upper left hand corner of a tile.
sf::Vector2f Map::tileToPixel (int x, int y) const
{
  return sf::Vector2f(x * tileSize, y * tileSize);
}
sf::Vector2f Map::tileToPixel (sf::Vector2i coords) const
{ return tileToPixel(coords.x, coords.y); }

// Get the offset from a given location to the corner of its tile.
sf::Vector2f Map::pixelModTile (float x, float y) const
{
  return sf::Vector2f((int)x % tileSize, (int)y % tileSize);
}
sf::Vector2f Map::pixelModTile (sf::Vector2f coords) const
{ return pixelModTile(coords.x, coords.y); }

// Get the bounds of the tiles that cover a bounded region on the screen.
sf::IntRect Map::pixelToTileBounds (sf::FloatRect bounds) const
{
  sf::Vector2i ltCorner = pixelToTile(bounds.left, bounds.top);
  // This calculation accounts for areas that exactly line up with the tiles
  // and those that end somewhere in the middle, snapping down and right.
  sf::Vector2i rbCorner =
      pixelToTile(bounds.left + bounds.width + (float)tileSize - 0.25f,
                  bounds.top + bounds.height + (float)tileSize - 0.25f);
  sf::Vector2i size(rbCorner.x - ltCorner.x, rbCorner.y - ltCorner.y);

  return sf::IntRect(ltCorner, size);
}
