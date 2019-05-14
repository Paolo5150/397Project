#include "GameAssetFactory.h"
#include "..\Prefabs\Water.h"
#include "..\Prefabs\Terrain.h"
#include "..\Core\MainCamera.h"
#include "..\Prefabs\Barrel.h"
#include "..\Prefabs\Cabin.h"
#include "..\Prefabs\Crate.h"
#include "..\Prefabs\Gun.h"
#include "..\Prefabs\Hive.h"
#include "..\Prefabs\Mountains.h"
#include "..\Prefabs\Player.h"
#include "..\Prefabs\Pumpkin.h"
#include "..\Prefabs\PumpkinBunch.h"
#include "..\Prefabs\Spider.h"
#include "..\Prefabs\Ship.h"
#include "..\Prefabs\Tree.h"


GameAssetFactory GameAssetFactory::Instance()
{
	static GameAssetFactory instance;
	return instance;
}

GameAssetFactory::GameAssetFactory()
{

}
GameAssetFactory::~GameAssetFactory()
{

}

void GameAssetFactory::CleanUp()
{
	for (int i = 0; i < toBeDeletedASsets.size(); i++)
		delete toBeDeletedASsets[i];
}


InternalAsset* GameAssetFactory::Create(std::string type, std::string name)
{


	if (type == "Water")
		return new Water();
	else if (type == "MainCamera")
		return new MainCamera();
	else if (type == "GameObject")
		return new GameObject(name);
	else if (type == "Material")
	{
		Material*m = new Material();
		toBeDeletedASsets.push_back(m);
		return m;
	}
	else if (type == "Model")
		return AssetLoader::Instance().GetAsset<Model>(name)->CreateGameObject();
	else if (type == "Barrel")
		return new Barrel();
	else if (type == "Cabin")
		return new Cabin();
	else if (type == "Crate")
		return new Crate();
	else if (type == "Gun")
		return new Gun();
	else if (type == "Hive")
		return new Hive();
	else if (type == "Mountains")
		return new Mountains();
	else if (type == "Player")
		return new Player();
	else if (type == "Pumpkin")
		return new Pumpkin();
	else if (type == "PumpkinBunch")
		return new PumpkinBunch();
	else if (type == "Ship")
		return new Ship();
	else if (type == "Spider")
		return new Spider();
	else if (type == "Tree")
		return new Tree();
}