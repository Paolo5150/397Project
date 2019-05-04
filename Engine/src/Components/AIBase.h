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

	float GetReverseRotationToTarget() const; //Same as above but reversed by 180 degrees

	Transform* GetTarget() const;

	void SetState(std::string state);

	std::string GetState() const;

	void Move(float forward = 0.0f, float right = 0.0f);

	void Rotate(float amount = 0.0f);

	void SetAnimation(int index = 0);

	void Update() override;

	virtual void OnAttach(GameObject* go) override;

private:
	std::string _state;
	Transform* _parentTransform;
	Transform* _targetTransform;
	lua_State* _luaState;

	std::string _scriptPath;

	float _wanderDirection;
	float _lastStateChange; //Time since the last succesful state change
	float _randomTimer; //Timer for managing random state changes

	//AI Functions
	void Think();
	//----------
};

