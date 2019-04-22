#include "RigidBody.h"
#include "..\Utils\Maths.h"
#include "..\Physics\PhysicsWorld.h"



void RigidBody::OnAttach(GameObject* go)
{
	if (_collider == nullptr)
	{
		if (go->GetComponentByType<Collider>("Collider"))
		{
			_collider = go->GetComponentByType<Collider>("Collider");
			InitBTRB(go);

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

void RigidBody::OnGameObjectAddedToScene(GameObject* go)
{
	PhysicsWorld::Instance().AddRigidBody(this);
}

void RigidBody::Update()
{
	if (!_isActive) return;

	btTransform t;
	btrb->getMotionState()->getWorldTransform(t);

	float xtans = t.getOrigin().getX() - prevPos.getOrigin().getX();
	float ytans = t.getOrigin().getY() - prevPos.getOrigin().getY();
	float ztans = t.getOrigin().getZ() - prevPos.getOrigin().getZ();

	//Logger::LogWarning("Y trans", ytans);
	//Logger::LogWarning("In update, y is", t.getOrigin().getY());
	Logger::LogWarning("In rigidbody, collider y", _collider->transform.GetGlobalPosition().y);
	//Logger::LogError("y trans", ytans);

	prevPos = t;


	transform->Translate(xtans, ytans, ztans);


}

void RigidBody::PrePhysicsUpdate()
{


}


void RigidBody::InitBTRB(GameObject* go)
{

	transform = &go->GetRoot()->transform;
	transform->Update();
	_collider->transform.Update();

	_collider->collisionShape->calculateLocalInertia(mass, btVector3(intertia.x,intertia.y,intertia.z));


	motionState = new btDefaultMotionState(btTransform(btQuaternion(), btVector3(_collider->transform.GetGlobalPosition().x, _collider->transform.GetGlobalPosition().y, _collider->transform.GetGlobalPosition().z)));
	prevPos.setOrigin(btVector3(_collider->transform.GetGlobalPosition().x, _collider->transform.GetGlobalPosition().y, _collider->transform.GetGlobalPosition().z));
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
		mass,                  // mass, in kg. 0 -> Static object, will never move.
		motionState,
		_collider->collisionShape,  // collision shape of body
		btVector3(intertia.x, intertia.y, intertia.z)    // local inertia
		);

	btrb = new btRigidBody(rigidBodyCI);
	

}