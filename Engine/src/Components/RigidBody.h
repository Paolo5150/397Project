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
			InitBTRB();


	}

	~RigidBody();
	void OnAttach(GameObject* go) override;
	void Update() override;
	glm::vec3 intertia;

private:
	Transform* transform;
	Collider* _collider;
	btRigidBody* btrb;
	btMotionState* motionState;
	void InitBTRB();
	float mass;
};