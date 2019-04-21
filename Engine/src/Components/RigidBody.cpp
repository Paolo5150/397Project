#include "RigidBody.h"
#include "..\Physics\PhysicsWorld.h"

void RigidBody::OnAttach(GameObject* go)
{
	if (_collider == nullptr)
	{
		if (go->GetComponentByType<Collider>("Collider"))
		{
			_collider = go->GetComponentByType<Collider>("Collider");
			InitBTRB();
			PhysicsWorld::Instance().AddRigidBody(this);

		}
		else
		{
			Logger::LogError("Rigidbody needs a collider!");
			abort();
		}
	}
}

RigidBody::~RigidBody()
{
	PhysicsWorld::Instance().RemoveRigidBody(this);

}


void RigidBody::Update()
{
	btTransform t;
	btrb->getMotionState()->getWorldTransform(t);

	float mat[16];
	t.getOpenGLMatrix(mat);
	glm::mat4 trans = glm::make_mat4(mat);

	trans *= transform->GetMatrix();
	
	transform->SetPosition(trans[3][0], trans[3][1], trans[3][2]);
	//transform.Update();

	Logger::LogInfo("gy", _parent->transform.GetGlobalPosition().y);
}

void RigidBody::InitBTRB()
{


	_collider->collisionShape->calculateLocalInertia(mass, btVector3(intertia.x,intertia.y,intertia.z));

	motionState = new btDefaultMotionState();
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
		mass,                  // mass, in kg. 0 -> Static object, will never move.
		motionState,
		_collider->collisionShape,  // collision shape of body
		btVector3(intertia.x, intertia.y, intertia.z)    // local inertia
		);

	btrb = new btRigidBody(rigidBodyCI);
	
	transform = &_parent->transform;

}