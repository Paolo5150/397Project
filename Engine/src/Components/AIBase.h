#pragma once
#include <string>

#include "..\GameObject\Component.h"
#include "Animator.h"
#include "..\Core\Timer.h"
#include "..\Core\Lua.h"
#include "..\Utils\PathFinder.h"
#include "..\Prefabs\Terrain.h"

class AIBase : public Component
{
public:
	AIBase(std::string scriptPath); //Note: do not call a seeking function without setting a target first!

	AIBase(Transform& targetTransform, std::string scriptPath);

	~AIBase();

	void SetTarget(Transform& targetTransform);

	float GetDistanceToTarget() const;

	float GetRotationToTarget() const;

	float GetReverseRotationToTarget() const; //Same as above but reversed by 180 degrees

	float GetDistanceToNode() const;

	float GetRotationToNode() const;

	float GetReverseRotationToNode() const; //Same as above but reversed by 180 degrees

	Transform* GetTarget() const;

	void SetState(std::string state);

	std::string GetState() const;

	void SetEventReceived(bool received);

	bool GetEventReceived() const;

	void Move(float forward = 0.0f, float right = 0.0f);

	void MoveForward(float forward = 0.0f);

	void MoveRight(float right = 0.0f);

	void Rotate(float amount = 0.0f);

	void SetAnimation(int index = 0);

	void Update() override;

	virtual void OnAttach(GameObject* go) override;

private:
	std::string _state;
	Transform* _parentTransform;
	Transform* _targetTransform;
	lua_State* _luaState;
	glm::vec3 _otherTarget; //Postition that can be used for wandering/patrolling or any other location based logic
	glm::vec3 _nextNode;
	bool _eventReceived;

	std::string _scriptPath;

	float _lastStateChange; //Time since the last succesful state change
	float _randomTimer; //Timer for managing random state changes
	float _updateTimer;

	//AI Functions
	void Think();
	//----------
};

