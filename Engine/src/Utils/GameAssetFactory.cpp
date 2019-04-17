#include "GameAssetFactory.h"
#include "..\Prefabs\Water.h"
#include "..\Prefabs\Terrain.h"
#include "..\Core\MainCamera.h"


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
}