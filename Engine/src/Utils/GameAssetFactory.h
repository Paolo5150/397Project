#pragma once
#include "..\GameObject\GameObject.h"
#include "AssetLoader.h"


class GameAssetFactory
{
public:
	static GameAssetFactory Instance();
	~GameAssetFactory();


	InternalAsset* Create(std::string type,std::string name = "");
	void CleanUp();


private:
	GameAssetFactory();
};


