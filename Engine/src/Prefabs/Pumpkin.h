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
	static float GetDamageGiven(){ return damageGiven; }

private:
	static float damageGiven;
	float speed;
	float lifeTimer;
};