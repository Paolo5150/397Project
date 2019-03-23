#pragma once

struct Layers
{
	enum LayerNames
	{
		DEFAULT = 1 << 0,
		WATER = 1 << 1,
		GUI = 1 << 2,
		TERRAIN = 1 << 3
	};
};