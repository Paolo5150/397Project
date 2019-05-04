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


void PathFinder::NodeAt(int x, int z)
{

}

void PathFinder::Generate(Terrain* terrain)
{
	for (int x = terrain->GetTerrainMinX() + 200; x < terrain->GetTerrainMaxX() - 200; x += 180)
	{
		for (int z = terrain->GetTerrainMinZ() + 200; z < terrain->GetTerrainMaxZ() - 200; z += 180)
		{
			PathNode* pn = new PathNode();
			pn->transform.SetPosition(x, terrain->GetHeightAt(x, z), z);
			pathNodes.push_back(pn);

		}
	}

	int x, y, z;
	terrain->GetCenter(x, y, z);
	nodesQT = new QuadTree<PathNode*>(x, z, terrain->GetTerrainMaxX() - terrain->GetTerrainMinX(), terrain->GetTerrainMaxZ() - terrain->GetTerrainMinZ());

	for (unsigned i = 0; i < pathNodes.size(); i++)
		nodesQT->AddElement(pathNodes[i], pathNodes[i]->sc->transform.GetGlobalPosition().x, pathNodes[i]->sc->transform.GetGlobalPosition().z, pathNodes[i]->sc->transform.GetGlobalScale().x, pathNodes[i]->sc->transform.GetGlobalScale().z);
}

