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


	prevPos = t;
	transform->Translate(xtans, ytans, ztans);
	transform->SetRotation(t.getRotation().getX(), t.getRotation().getY(), t.getRotation().getZ(), t.getRotation().getW());


}

void RigidBody::PrePhysicsUpdate()
{


}


void RigidBody::InitBTRB(GameObject* go)
{
	
	transform = &go->GetRoot()->transform;
	transform->Update();
	_collider->transform.Update();

	btVector3 intert;
	_collider->collisionShape->calculateLocalInertia(mass, intert);
	
	motionState = new btDefaultMotionState(btTransform(btQuaternion(1,0,0,0), btVector3(_collider->transform.GetGlobalPosition().x, _collider->transform.GetGlobalPosition().y, _collider->transform.GetGlobalPosition().z)));
	prevPos.setOrigin(btVector3(_collider->transform.GetGlobalPosition().x, _collider->transform.GetGlobalPosition().y, _collider->transform.GetGlobalPosition().z));
	
	//intertia = glm::vec3(1,1,1);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
		mass,                  // mass, in kg. 0 -> Static object, will never move.
		motionState,
		_collider->collisionShape,  // collision shape of body
		intert   // local inertia
		);

	btrb = new btRigidBody(rigidBodyCI);
	/*btrb->setFriction(0.5);
	btrb->setRollingFriction(0.2);
	btrb->setRestitution(0.1);
	btrb->activate();*/
	//btrb->setCenterOfMassTransform((btTransform(btQuaternion(), btVector3(_collider->transform.GetGlobalPosition().x, _collider->transform.GetGlobalPosition().y, _collider->transform.GetGlobalPosition().z))));

}