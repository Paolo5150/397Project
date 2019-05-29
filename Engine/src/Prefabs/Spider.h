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

/**
* @class Spider
* @brief Premade gameobject for the Spider object
*
*
* @author Dylan Green
* @version 01
* @date 10/05/2019
*
*
* @bug No known bugs.
*/
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

private:

	static unsigned totalSpiders;
	static unsigned totalSpidersKilled;
	AIBase* aiBase;
	HealthComponent* healthComponent;
	float attackTimer;
	float deathTimer;

	/**
	* @brief		Timer for drowning
	*/
	float underwaterTimer;
	std::string _enemySpottedEventID;
	BoxCollider* pumpkinCollider;
	BoxCollider* slowCollider;
	Companion* companion;
	Player* player;

	bool EnemySpotted(Event* e);
};

