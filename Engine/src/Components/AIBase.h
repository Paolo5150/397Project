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
	AIBase(Transform targetTransform, AIState state = AIState::Wander);
	~AIBase();

	float GetBearing() const;

	void SetTarget(Transform targetTransform);

	float GetDistanceToTarget() const;

	int GetBearingToTarget() const;

	Transform* GetTarget() const;

	void SetState(AIState state);

	AIState GetState() const;

	void SetMovementSpeed(float movementSpeed);

	float GetMovementSpeed() const;

	void SetRotationSpeed(float rotationSpeed);

	float GetRotationSpeed() const;

	void SetFleeDistance(float fleeDistance);

	float GetFleeDistance() const;

	void SetAgroDistance(float agroDistance);

	float GetAgroDistance() const;

	void SetMaxFollowDistance(float maxFollowDistance);

	float GetMaxFollowDistance() const;

	void Update() override;

	virtual void OnAttach(GameObject* go) override;

private:
	AIState _state;
	Transform* _parentTransform;
	Transform* _targetTransform;

	float _targetDirection;
	float _movementSpeed;
	float _rotationSpeed;
	float _lastStateChange;

	float _fleeDistance; //Distance the ai will try and get to before stopping fleeing
	float _agroDistance; //Distance the ai will notice and start following the target
	float _maxFollowDistance; //Distance the ai will stop following the target

	double pi = 3.1415926535897;

	//AI Functions
	void Think();
	void Idle();
	void Wander();
	void Seek();
	void Fight();
	void Flee();
	//----------
};

