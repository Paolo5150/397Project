#pragma once

struct CollisionLayers
{
	enum CollisionLayerNames
	{
		DEFAULT = 1 << 0,
		PLAYER = 1 << 1,
		ENEMY = 1 << 2,
		OBSTACLE = 1 << 3,
		PATHNODE = 1 << 4
	};
};