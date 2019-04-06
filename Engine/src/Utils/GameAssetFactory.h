#pragma once
#include "..\GameObject\GameObject.h"
#include "AssetLoader.h"
class GameAssetFactory
{
public:
	GameAssetFactory();
	~GameAssetFactory();

	template <class T>
	static GameObject* Create(std::string name = "");


private:

};

template <class T>
GameObject* GameAssetFactory::Create(std::string name)
{
	std::string typeName = typeid(T).name();

	if (typeName == "Model")
		return AssetLoader::Instance().GetAsset<Model>(name)->CreateGameObject();
	else
		return new T();
}