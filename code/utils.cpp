#include "utils.hpp"

// or the image-lib.hpp
#include "image-def.hpp"


// see header
float blocksToPixels (int blocks)
{
  return (int)(blocks * (float)tileSize);
}

// see header
int pixelsToBlocks (float pixels)
{
  return (float)pixels / (float)tileSize;
}
