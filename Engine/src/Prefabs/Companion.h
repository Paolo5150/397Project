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
		RUN = 10,
		WALK = 12
	};

	Companion();
	~Companion();
	void Start() override;
	void Update() override;


private:

	GameObject* playerRef;
	Animator* animator;
	HealthComponent* healthComponent;

};