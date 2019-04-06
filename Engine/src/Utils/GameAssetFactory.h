#pragma once
#include "..\GameObject\GameObject.h"
#include "AssetLoader.h"


class GameAssetFactory
{
public:
	GameAssetFactory();
	~GameAssetFactory();


	static InternalAsset* Create(std::string type,std::string name = "");


private:

};


