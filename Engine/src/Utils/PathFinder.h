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
	~PathFinder();
	void ClosestNodeAt(int x, int y, int z);

	void Start();
	QuadTree<PathNode*>* nodesQT;
	std::vector<std::vector<PathNode*>> nodeMap;

	std::vector<PathNode*> pathNodes;
private:
	PathFinder();
};