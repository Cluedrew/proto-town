#ifndef PHYSICS_TILE_HPP
#define PHYSICS_TILE_HPP

/* Repersenting the physics of a tile.
 * Since tiles are locked to the grid structure of the Map and don't move
 * this is centered on the collider that Mobs can run into.
 */

struct PhysicsTile
{
  // Currently this is all the data we need.
  bool isPassible;
};

#endif//PHYSICS_TILE_HPP
