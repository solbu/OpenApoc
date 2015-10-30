#pragma once
#include "library/sp.h"

#include "framework/includes.h"
#include "game/tileview/tileobject.h"
#include <set>
#include <functional>
#include <vector>

namespace OpenApoc
{

class Framework;
class Image;
class TileMap;
class Tile;
class Collision;
class VoxelMap;
class Renderer;
class TileView;
class Projectile;
class TileObjectProjectile;
class Vehicle;
class TileObjectVehicle;
class Scenery;
class TileObjectScenery;
class Doodad;
class TileObjectDoodad;

class Tile
{
  public:
	TileMap &map;
	Vec3<int> position;

	std::set<sp<TileObject>> ownedObjects;
	std::set<sp<TileObject>> intersectingObjects;

	// FIXME: This is effectively a z-sorted list of ownedObjects - can this be merged somehow?
	std::vector<sp<TileObject>> drawnObjects;

	Tile(TileMap &map, Vec3<int> position);

	Collision findCollision(Vec3<float> lineSegmentStart, Vec3<float> lineSegmentEnd);
};

class CanEnterTileHelper
{
  public:
	// Returns true if this object can move from 'from' to 'to'. The two tiles must be adjacent!
	virtual bool canEnterTile(Tile *from, Tile *to) const = 0;
};

class TileMap
{
  private:
	std::vector<Tile> tiles;

  public:
	Framework &fw;
	Tile *getTile(int x, int y, int z);
	Tile *getTile(Vec3<int> pos);
	// Returns the tile this point is 'within'
	Tile *getTile(Vec3<float> pos);
	Vec3<int> size;

	TileMap(Framework &fw, Vec3<int> size);
	~TileMap();

	std::list<Tile *> findShortestPath(Vec3<int> origin, Vec3<int> destination,
	                                   unsigned int iterationLimit,
	                                   const CanEnterTileHelper &canEnterTile);

	Collision findCollision(Vec3<float> lineSegmentStart, Vec3<float> lineSegmentEnd);

	sp<TileObjectProjectile> addObjectToMap(sp<Projectile>);
	sp<TileObjectVehicle> addObjectToMap(sp<Vehicle>);
	sp<TileObjectScenery> addObjectToMap(sp<Scenery>);
	sp<TileObjectDoodad> addObjectToMap(sp<Doodad>);
};
}; // namespace OpenApoc
