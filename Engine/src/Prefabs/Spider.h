#pragma once
#include <string>

#include "../GameObject/GameObject.h"
#include "../GameObject/Saveable.h"
#include "..\Utils\AssetLoader.h"

class AIBase;
class HealthComponent;
class BoxCollider;
class Companion;
class Player;


class Spider : public GameObject, public Saveable
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

	std::string Save() override;

	void OnCollision(GameObject* g) override;

	static unsigned GetTotalSpiders(){ return totalSpiders; }
	static unsigned GetTotalSpidersKilled(){ return totalSpidersKilled; }
	static void ResetTotalSpidersKilled() { totalSpidersKilled = 0; }

	AIBase* aiBase;
	HealthComponent* healthComponent;

private:

	static unsigned totalSpiders;
	static unsigned totalSpidersKilled;

	float attackTimer;
	float deathTimer;
	float underwaterTimer;
	std::string _enemySpottedEventID;
	BoxCollider* pumpkinCollider;
	BoxCollider* slowCollider;
	Companion* companion;
	Player* player;

	bool EnemySpotted(Event* e);
};

