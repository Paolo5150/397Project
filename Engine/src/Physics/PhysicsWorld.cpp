#include "PhysicsWorld.h"

namespace
{

}

PhysicsWorld&  PhysicsWorld::Instance()
{
	static PhysicsWorld instance;
	return instance;
}


PhysicsWorld::PhysicsWorld()
{
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
	// Set up the collision configuration and dispatcher
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	// The actual physics solver
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
	// The world.
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	SetGravity(0.0f, 0.0f, 0.0f);
	

}

PhysicsWorld::~PhysicsWorld()
{
	
	allRigidBodies.clear();


	delete dynamicsWorld;
}

void PhysicsWorld::AddRigidBody(RigidBody* rb)
{
	allRigidBodies.push_back(rb);
	dynamicsWorld->addRigidBody(rb->btrb);
}

void PhysicsWorld::RemoveRigidBody(RigidBody* rb)
{
	auto it = allRigidBodies.begin();

	for (; it != allRigidBodies.end();)
	{
		if ((*it) == rb)
		{
			it = allRigidBodies.erase(it);
			dynamicsWorld->removeRigidBody((*it)->btrb);
		}
		else
			it++;
	}
}



void PhysicsWorld::SetGravity(float x, float y, float z)
{
	dynamicsWorld->setGravity(btVector3(x,y,z));

}

void PhysicsWorld::Update(float deltaS)
{
	auto it = allRigidBodies.begin();
	for (; it != allRigidBodies.end(); it++)
		(*it)->PrePhysicsUpdate();

	dynamicsWorld->updateAabbs();
	
	dynamicsWorld->stepSimulation(deltaS, 10);
}

bool PhysicsWorld::CollisionCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
{
	Logger::LogInfo("Collision");
	return false;
}


