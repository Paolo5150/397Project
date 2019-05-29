#include <string>

#include "../GameObject/GameObject.h"
#include "..\GameObject\Saveable.h"
#include "..\Utils\AssetLoader.h"
#include "..\Components\HealthComponent.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Animator.h"
#include "Player.h"

/**
* @class Companion
* @brief Specialized entity that defines a Companion.
*
* @author Paolo Ferri
* @version 01
* @date 25/05/2019
*
*
* @bug No known bugs.
*/
class Companion : public GameObject, Saveable
{
public:

	enum ANIMATION
	{
		BITE = 1,
		ATTACK = 3,
		DEATH = 5,
		DEATH2 = 6,
		IDLE = 7,
		IDLE2 = 8,
		SLEEP = 10,
		RUN = 11,
		WALK = 12
	};

	enum STATE
	{
		FOLLOW_STATE = 500,
		IDLE_STATE,
		ATTACK_STATE,
		DEAD_STATE,
		CHARGE_STATE
	};

	/**
	* @brief		Constructor
	* @pre			The companion object does not exist
	* @post			The companion object is created
	*/
	Companion();

	/**
	* @brief		Destructor
	* @pre			The companion object must exist
	* @post			The companion object is destroyed
	*/
	~Companion();

	/**
	* @brief		Initialize player
	* @pre			The companion object must exist
	* @post			The companion object is initialized, colliders are added
	*/
	void Start() override;

	/**
	* @brief		Overridden callback for update method
	* @pre			The companion object must exist
	*/
	void Update() override;

	/**
	* @brief		Overridden callback for save method
	* @pre			The hive object must exist
	*
	* @return		String containing information to be saved
	*/
	std::string Save() override;

	/**
	* @brief		Set a target for the companion to attack
	* @pre			The companion object must exist
	*/
	void SetTarget(GameObject* target);

	HealthComponent* GetHealthComponent() { return healthComponent; }

	/**
	* @brief		The current state
	*/
	STATE currentState;
private:

	/**
	* @brief		Reference to the player object
	*/
	GameObject* playerRef;

	/**
	* @brief		Reference to animator component
	*/
	Animator* animator;

	/**
	* @brief		Reference to health component
	*/
	HealthComponent* healthComponent;


	/**
	* @brief		Reference to current target
	*/
	GameObject* target;

	/**
	* @brief		Idle state method
	*/
	void Idle();

	/**
	* @brief		Follow player around the level
	*/
	void FollowPlayer();

	/**
	* @brief		Run towards current target
	*/
	void Charge();

	/**
	* @brief		Play dead animation
	*/
	void Die();

	/**
	* @brief		Walk towards current target
	*/
	void GoToTarget();
	/**
	* @brief		Attack the current target
	* @pre			The companion object must exist
	*/
	void Attack();

	void CheckForSpiders();

	/**
	* @brief		Companion damage when attacking
	*/
	float attackDamage;

	/**
	* @brief		Walking speed
	*/
	float walkSpeed;

	/**
	* @brief		Running speed
	*/
	float runSpeed;

	/**
	* @brief		Current movememnt speed
	*/
	float currentSpeed;


	

};