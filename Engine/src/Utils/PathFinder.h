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
	PathNode* ClosestNodeAt(int x, int y, int z);

	void Start();
	QuadTree<PathNode*>* nodesQT;
	std::vector<std::vector<PathNode*>> nodeMap;

	glm::vec3 GetRandomFreeNodePosition();
	std::vector<glm::vec3> GeneratePath(glm::vec3 start, glm::vec3 finish);
	std::vector<PathNode*> pathNodes;
private:
	PathFinder();
};