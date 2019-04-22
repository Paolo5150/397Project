#pragma once


#include "Collider.h"

class RigidBody : public Component
{
public:
	friend class PhysicsWorld;

	RigidBody(float mass = 0, Collider* collider = nullptr) : Component("RigidBody")
	{
		_collider = collider;
		this->mass = mass;
		if (_collider != nullptr)
			InitBTRB(_parent);


	}

	~RigidBody();
	void OnAttach(GameObject* go) override;
	void OnGameObjectAddedToScene(GameObject* go) override;
	void Update() override;
	void PrePhysicsUpdate();
	glm::vec3 intertia;

	btRigidBody* btrb;
private:
	Transform* transform;
	Collider* _collider;
	btMotionState* motionState;
	void InitBTRB(GameObject* go);
	btTransform prevPos;
	float mass;
};