#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"
#include "..\Scene\SceneManager.h"
#include "..\Scene\Scene.h"


class Ship : public GameObject
{
public:
	Ship();
	~Ship();
	void Start() override;
private:

};