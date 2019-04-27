#pragma once
#include <string>

#include "..\GameObject\Component.h"
#include "AIState.h"
#include "..\Utils\RandUtils.h"

class AI_Enemy : public Component
{
public:
	AI_Enemy(AIState state = AIState::Wander);
	~AI_Enemy();

	void SetState(AIState state);

	AIState GetState() const;

	void Update() override;

private:
	AIState _state;
	Transform _parentTransform;
	float _moveDir;

	void Think();
	void Wander();
	void Seek();
	void Fight();
	void Flee();
};

