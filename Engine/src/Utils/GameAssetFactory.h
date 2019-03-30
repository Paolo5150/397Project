#pragma once
#include "..\GameObject\GameObject.h"
class GameAssetFactory
{
public:
	GameAssetFactory();
	~GameAssetFactory();

	template <class T>
	GameObject* Create(std::string name);


private:

};

template <class T>
GameObject* Create(std::string name);