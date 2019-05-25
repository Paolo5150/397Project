#include <string>

#include "../GameObject/GameObject.h"
#include "..\Utils\AssetLoader.h"
#include "..\Components\HealthComponent.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\Animator.h"
#include "Player.h"


class Companion : public GameObject
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

	Companion();
	~Companion();
	void Start() override;
	void Update() override;
	void SetTarget(GameObject* target);
	void Attack();

	STATE currentState;
private:

	GameObject* playerRef;
	Animator* animator;
	HealthComponent* healthComponent;
	GameObject* target;
	void Idle();
	void FollowPlayer();
	void Charge();
	void GoToTarget();

	float walkSpeed;
	float runSpeed;
	float currentSpeed;


	

};