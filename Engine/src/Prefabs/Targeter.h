#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"

class Companion;

class Targeter : public GameObject
{
public:

	Targeter();
	~Targeter();
	void Start() override;

	void Update() override;

	glm::vec3 shootDirection;


private:
	Companion* companionRef;
	float speed;
	float lifeTimer;
};