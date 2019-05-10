#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"
#

class Pumpkin : public GameObject
{
public:
	enum STATE
	{
		SHOT,
		GROUND
	};

	Pumpkin();
	~Pumpkin();
	void Start() override;
	STATE state;

	void Update() override;

	glm::vec3 shootDirection;
private:
	float speed;
};