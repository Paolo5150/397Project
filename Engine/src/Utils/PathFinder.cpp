#include "PathFinder.h"
#include "..\Prefabs\Terrain.h"

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


void PathFinder::ClosestNodeAt(int x, int y,  int z)
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

	//closest->sc->meshRenderer->GetMaterial().SetColor(1, 1, 0);
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