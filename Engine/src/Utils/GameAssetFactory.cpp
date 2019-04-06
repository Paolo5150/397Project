#include "GameAssetFactory.h"
#include "..\Prefabs\Water.h"
#include "..\Prefabs\Terrain.h"
#include "..\Core\MainCamera.h"


GameAssetFactory::GameAssetFactory()
{

}
GameAssetFactory::~GameAssetFactory()
{

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
		return new Material();
	else if (type == "Model")
		return AssetLoader::Instance().GetAsset<Model>(name)->CreateGameObject();
}