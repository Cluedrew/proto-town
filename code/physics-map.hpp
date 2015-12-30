#ifndef PHYSICS_MAP
#define PHYSICS_MAP

/* Physics data for the map.
 *
 * Note that unlike some of the other physics data stuctures this is more
 * about wrapping up access of existing information rather than introducing
 * new information. It's basic purpose however, putting information for
 * physics calculations in the same place, is the same.
 */

#include "physics-tile.hpp"

class PhysicsMap
{
private:
  // Reference to the map.
  Map const & map;

  // Physics for the void, spaces outside the map.
  PhysicsTile const voidPhysicsTile;

protected:
public:
  PhysicsMap (Map const & map, PhysicsTile voidTile = PhysicsTile()) :
      map(map), voidPhysicsTile(voidTile)
  {}
  /* Construct a PhysicsMap.
   */

  PhysicsTile const & at (int x, int y)
  /*
   */
  {
    if (0 <= x && x < map.width() && 0 <= y && y < map.height())
      return map.at(x,y).getPhysics();
    else
      return voidPhysicsTile;
  }
}

#endif//PHYSICS_MAP
