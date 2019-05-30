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
	/**
	* @brief		Constructor
	*
	* @pre			The spider object does not exist
	* @post			The spider object is created
	*/
	Spider();

	/**
	* @brief		Constructor
	*
	* @pre			The spider object does not exist
	* @post			The spider object is created
	*
	* @param		posX	x position to spawn the spider at
	* @param		posY	y position to spawn the spider at
	* @param		posZ	z position to spawn the spider at
	*/
	Spider(float posX, float posY, float posZ);

	/**
	* @brief		Constructor
	*
	* @pre			The spider object does not exist
	* @post			The spider object is created
	*
	* @param		targetTransform	transform of the target
	*/
	Spider(Transform& targetTransform);

	/**
	* @brief		Constructor
	*
	* @pre			The spider object does not exist
	* @post			The spider object is created
	*
	* @param		targetTransform	transform of the target
	* @param		posX	x position to spawn the spider at
	* @param		posY	y position to spawn the spider at
	* @param		posZ	z position to spawn the spider at
	*/
	Spider(Transform& targetTransform, float posX, float posY, float posZ);

	/**
	* @brief		Destructor
	*
	* @pre			The spider object must exist
	* @post			The spider object is destroyed
	*/
	~Spider();

	/**
	* @brief		Sets the target for the spider's AIBase
	*
	* @param		transform	transform of the target
	*/
	void SetTarget(Transform& transform);

	/**
	* @brief		Returns the spider's target transform
	*
	* @return		the spider's target transform
	*/
	Transform* GetTarget() const;

	/**
	* @brief		Initialize spider
	*
	* @pre			The spider object must exist
	* @post			The spider object is initialized, colliders are added
	*/
	void Start() override;

	/**
	* @brief		Overridden callback for update method
	*
	* @pre			The spider object must exist
	*/
	void Update() override;

	/**
	* @brief		Overridden callback for save method
	*
	* @pre			The spider object must exist
	*
	* @return		String containing information to be saved
	*/
	std::string Save() override;

	/**
	* @brief		Overridden callback for oncollision method
	*
	* @pre			The spider object must exist
	*/
	void OnCollision(GameObject* g) override;

	/**
	* @brief		returns total number of spiders
	* @return		The total number of spiders
	*/
	static unsigned GetTotalSpiders(){ return totalSpiders; }

	/**
	* @brief		sets total number of spiders killed
	* @param		spidersKilled	the total number of spiders killed
	*/
	static void SetTotalSpidersKilled(unsigned spidersKilled) { totalSpidersKilled = spidersKilled; }

	/**
	* @brief		returns total number of spiders killed
	* @return		the total number of spiders killed
	*/
	static unsigned GetTotalSpidersKilled(){ return totalSpidersKilled; }

	/**
	* @brief		Reset total number of spiders killed
	*/
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

