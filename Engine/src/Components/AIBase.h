#pragma once
#include <string>

#include "..\GameObject\Component.h"
#include "Animator.h"
#include "AIState.h"
#include "..\Utils\RandUtils.h"
#include "..\Core\Timer.h"
#include "..\Core\Lua.h"

class AIBase : public Component
{
public:
	AIBase(std::string scriptPath, AIState state = AIState::Idle); //Note: do not call a seeking function without setting a target first!

	AIBase(Transform& targetTransform, std::string scriptPath, AIState state = AIState::Idle);

	~AIBase();

	void SetTarget(Transform& targetTransform);

	float GetDistanceToTarget() const;

	float GetRotationToTarget() const;

	Transform* GetTarget() const;

	void SetState(std::string state);

	std::string GetState() const;

	void Move(float forward = 0.0f, float right = 0.0f);

	void Rotate(float amount = 0.0f);

	void SetAnimation(int index);

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

	void SetAttackDistance(float attackDistance);

	float GetAttackDistance() const;

	void Update() override;

	virtual void OnAttach(GameObject* go) override;

private:
	std::string _state;
	Transform* _parentTransform;
	Transform* _targetTransform;
	lua_State* _luaState;

	std::string _scriptPath;

	float _wanderDirection;
	float _movementSpeed;
	float _rotationSpeed;
	float _lastStateChange; //Time since the last succesful state change
	float _randomTimer; //Timer for managing random state changes

	float _fleeDistance; //Distance the ai will try and get to before stopping fleeing
	float _agroDistance; //Distance the ai will notice and start following the target
	float _maxFollowDistance; //Distance the ai will stop following the target
	float _attackDistance; //Distance the ai will switch to fighting

	//Lua Functions
	void Lua_Think();
	//----------

	//AI Functions
	void Think();
	void Idle();
	void Wander();
	void Seek();
	void Fight();
	void Flee();
	//----------
};

