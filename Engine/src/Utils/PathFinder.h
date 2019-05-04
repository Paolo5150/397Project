#pragma once

#include "..\Components\PathNode.h"
#include <vector>

class Terrain;

class PathFinder
{
public:
	static PathFinder& Instance();
	void Generate(Terrain* terrain);

	void EngineUpdate();
	void Update();

	std::vector<PathNode*> pathNodes;
private:
	PathFinder();
};