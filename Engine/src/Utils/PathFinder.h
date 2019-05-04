#pragma once

#include "..\Components\PathNode.h"
#include "Quadtree.h"
#include <vector>

class Terrain;

class PathFinder
{
public:
	static PathFinder& Instance();
	void Generate(Terrain* terrain);

	void NodeAt(int x, int z);

	QuadTree<PathNode*>* nodesQT;

	std::vector<PathNode*> pathNodes;
private:
	PathFinder();
};