#include "PathFinder.h"
#include "..\Prefabs\Terrain.h"
#include <list>
#include <limits>
#include <float.h>
PathFinder& PathFinder::Instance()
{
	static PathFinder instance;
	return instance;

}

PathFinder::PathFinder()
{}

PathFinder::~PathFinder()
{
	delete nodesQT;
}


PathNode* PathFinder::ClosestNodeAt(int x, int y,  int z)
{
	std::set<PathNode*>& nodes = nodesQT->GameObjectsAt(x,z);

	double dist = 1000000000;
	PathNode* closest = nullptr;
	for (auto it = nodes.begin(); it != nodes.end(); it++)
	{
		if (closest == nullptr)
			closest = (*it);
		double length2 = glm::length2((*it)->sc->transform.GetGlobalPosition() - glm::vec3(x, y, z));
		
		if (length2 < dist)
		{
			dist = length2;
			closest = (*it);
		}
	
	}

	return closest;
}


void PathFinder::Generate(Terrain* terrain)
{
	int counterx = 0;
	for (int x = terrain->GetTerrainMinX() + 200; x < terrain->GetTerrainMaxX() - 200; x += 180)
	{
		std::vector<PathNode*> v;
		nodeMap.push_back(v);
		for (int z = terrain->GetTerrainMinZ() + 200; z < terrain->GetTerrainMaxZ() - 200; z += 180)
		{
			PathNode* pn = new PathNode();
			pn->transform.SetPosition(x, terrain->GetHeightAt(x, z), z);
			pn->transform.Update();
			pathNodes.push_back(pn);

			nodeMap[counterx].push_back(pn);

		}
		counterx++;

	}

	int x, y, z;
	terrain->GetCenter(x, y, z);
	nodesQT = new QuadTree<PathNode*>(x, z, terrain->GetTerrainMaxX() - terrain->GetTerrainMinX(), terrain->GetTerrainMaxZ() - terrain->GetTerrainMinZ());
	
	

}

void PathFinder::Start()
{

	for (unsigned i = 0; i < pathNodes.size(); i++)
		nodesQT->AddElement(pathNodes[i], pathNodes[i]->sc->transform.GetGlobalPosition().x, pathNodes[i]->sc->transform.GetGlobalPosition().z, pathNodes[i]->sc->transform.GetGlobalScale().x, pathNodes[i]->sc->transform.GetGlobalScale().z);

	int mapWidth = nodeMap.size();
	int mapHeight = nodeMap[0].size();

	for (int x = 0; x < nodeMap.size(); x++) {
		for (int y = 0; y < nodeMap[0].size(); y++) {

			if (x > 0) {
				nodeMap[x][y]->neighbors.push_back(nodeMap[x - 1][y]);

				//Diagonals

				if (y < mapHeight - 1) {
					nodeMap[x][y]->neighbors.push_back(nodeMap[x - 1][y + 1]);
				}

				if (y > 0) {
					nodeMap[x][y]->neighbors.push_back(nodeMap[x - 1][y - 1]);
				}
			}
			if (x < mapWidth - 1) {
				nodeMap[x][y]->neighbors.push_back(nodeMap[x + 1][y]);

				//Diagonals

				if (y < mapHeight - 1) {
					nodeMap[x][y]->neighbors.push_back(nodeMap[x + 1][y + 1]);
				}
				if (y > 0) {
					nodeMap[x][y]->neighbors.push_back(nodeMap[x + 1][y - 1]);
				}
			}
			if (y > 0) {
				nodeMap[x][y]->neighbors.push_back(nodeMap[x][y - 1]);
			}
			if (y < mapHeight - 1) {
				nodeMap[x][y]->neighbors.push_back(nodeMap[x][y + 1]);
			}
		}
	}



}

/*
void tes1()
{
	std::list<PathNode*> uncheckedNodes;
	std::vector<PathNode*> currentPath;
	for (unsigned i = 0; i < pathNodes.size(); i++)
	{
		if (pathNodes[i] != startNode)
		{
			pathNodes[i]->distanceFromSource = 999999999999999;
			pathNodes[i]->previousNode = nullptr;
		}
		uncheckedNodes.push_back(pathNodes[i]);
	}

	double dist = 999999999999999999;
	PathNode* nodeMinDistance = nullptr;
	for (auto it = uncheckedNodes.begin(); it != uncheckedNodes.end(); it++)
	{
		double length = glm::length((*it)->sc->transform.GetGlobalPosition() - startNode->sc->transform.GetGlobalPosition());

		if (length < dist)
		{
			nodeMinDistance = (*it);
			nodeMinDistance->distanceFromSource = length;
			dist = length;
		}

	}

	for (auto it1 = uncheckedNodes.begin(); it1 != uncheckedNodes.end();)
	{

		if (nodeMinDistance == goalNode)
			break;

		it1 = uncheckedNodes.erase(it1);

		for (unsigned i = 0; i < nodeMinDistance->neighbors.size(); i++)
		{
			double distance = nodeMinDistance->distanceFromSource + nodeMinDistance->neighbors[i]->DistanceTo(nodeMinDistance) + nodeMinDistance->neighbors[i]->cost;

			if (distance <  nodeMinDistance->neighbors[i]->distanceFromSource) {
				nodeMinDistance->neighbors[i]->distanceFromSource = distance;
				nodeMinDistance->neighbors[i]->previousNode = nodeMinDistance;

			}

		}
	}

	if (goalNode->previousNode == nullptr) {
		Logger::LogInfo("No path found");

	}
	else {

		PathNode* current = goalNode;
		while (current != nullptr) {
			currentPath.push_back(current);
			current = current->previousNode;
		}

		Logger::LogInfo("Path size", currentPath.size());
		for (unsigned i = 0; i < currentPath.size(); i++)
		{
			currentPath[i]->sc->enableRender = 1;
		}
	}
}*/

std::vector<glm::vec3> PathFinder::GeneratePath(glm::vec3 start, glm::vec3 finish)
{
	for (int i = 0; i < pathNodes.size(); i++)
		pathNodes[i]->sc->enableRender = 0;


	PathNode* startNode = ClosestNodeAt(start.x, start.y, start.z);
	PathNode* goalNode = ClosestNodeAt(finish.x, finish.y, finish.z);

	PathNode* currentNode = startNode;

	do
	{

		PathNode* shortest = nullptr;
		double minDist = 99999999999999999;
		for (unsigned i = 0; i < currentNode->neighbors.size(); i++)
		{
			currentNode->neighbors[i]->distanceFromPrevious = glm::length(currentNode->transform.GetPosition() - currentNode->neighbors[i]->transform.GetPosition());
			currentNode->neighbors[i]->distanceFromTarget = glm::length(goalNode->transform.GetPosition() - currentNode->neighbors[i]->transform.GetPosition());
			double total = currentNode->neighbors[i]->distanceFromPrevious + currentNode->neighbors[i]->distanceFromTarget + currentNode->neighbors[i]->cost;

			if (total < minDist)
			{
				shortest = currentNode->neighbors[i];
				minDist = total;
			}
		}

		shortest->previousNode = currentNode;
		currentNode = shortest;

	} while (currentNode != goalNode);


	while (currentNode->previousNode != nullptr)
	{
		currentNode->sc->meshRenderer->GetMaterial().SetColor(1, 0, 0);
		currentNode->sc->enableRender = 1;

		currentNode = currentNode->previousNode;
	}
	std::vector<glm::vec3> path;
	return path;

}
