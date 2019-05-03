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
	AIBase(std::string luaScriptFolder, AIState state = AIState::Idle); //Note: do not call a seeking function without setting a target first!

	AIBase(Transform& targetTransform, std::string luaScriptFolder, AIState state = AIState::Idle);

	~AIBase();

	void SetTarget(Transform& targetTransform);

	float GetDistanceToTarget() const;

	float GetRotationToTarget() const;

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

	void SetAttackDistance(float attackDistance);

	float GetAttackDistance() const;

	void Update() override;

	virtual void OnAttach(GameObject* go) override;

private:
	AIState _state;
	Transform* _parentTransform;
	Transform* _targetTransform;
	lua_State* _luaState;

	std::string _scriptFolderName;

	//float _wanderDirection;
	float _movementSpeed;
	float _rotationSpeed;
	float _lastStateChange;
	float _randomTimer; //Timer for managing 

	float _fleeDistance; //Distance the ai will try and get to before stopping fleeing
	float _agroDistance; //Distance the ai will notice and start following the target
	float _maxFollowDistance; //Distance the ai will stop following the target
	float _attackDistance; //Distance the ai will switch to fighting

	//AI Functions
	void Think();
	void Idle();
	void Wander();
	void Seek();
	void Fight();
	void Flee();
	//----------
};

