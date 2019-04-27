#pragma once
#include <string>

#include "..\GameObject\Component.h"
#include "AIState.h"
#include "..\Utils\RandUtils.h"
#include "..\Core\Timer.h"

class AIBase : public Component
{
public:
	AIBase(AIState state = AIState::Wander);
	~AIBase();

	void SetState(AIState state);

	void SetMoveSpeed(float moveSpeed);

	AIState GetState() const;

	float GetMoveSpeed() const;

	void Update() override;

	virtual void OnAttach(GameObject* go) override;

private:
	AIState _state;
	Transform* _parentTransform;
	float _moveDir;
	float _moveSpeed;

	void Think();
	void Wander();
	void Seek();
	void Fight();
	void Flee();
};

