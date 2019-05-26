#pragma once
#include <string>

#include "../GameObject/GameObject.h"
#include "..\Utils\AssetLoader.h"

class AIBase;
class HealthComponent;
class BoxCollider;



class Spider : public GameObject
{
public:
	Spider();

	Spider(float posX, float posY, float posZ);

	Spider(Transform& targetTransform);

	Spider(Transform& targetTransform, float posX, float posY, float posZ);

	~Spider();

	void SetTarget(Transform& transform);

	Transform* GetTarget() const;

	void Start() override;

	void Update() override;

	void OnCollision(GameObject* g) override;

	static unsigned GetTotalSpiders(){ return totalSpiders; }
	static unsigned GetTotalSpidersKilled(){ return totalSpidersKilled; }
	static void ResetTotalSpidersKilled() { totalSpidersKilled = 0; }

private:

	static unsigned totalSpiders;
	static unsigned totalSpidersKilled;
	AIBase* aiBase;
	float attackTimer;
	float deathTimer;
	HealthComponent* healthComponent;
	std::string _enemySpottedEventID;
	BoxCollider* pumpkinCollider;
	BoxCollider* slowCollider;

	bool EnemySpotted(Event* e);
};

