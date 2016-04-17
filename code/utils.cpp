#include "utils.hpp"

#include <cassert>
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

// see header
bool aEq (float lhs, float rhs, float diff)
{
  assert(0 <= diff);

  return (lhs - diff < rhs) && (rhs - diff < lhs);
}
