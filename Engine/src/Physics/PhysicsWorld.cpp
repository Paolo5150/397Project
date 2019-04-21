#include "PhysicsWorld.h"


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

}

PhysicsWorld::~PhysicsWorld()
{
	for (int i = 0; i < allRigidBodies.size(); i++)
		dynamicsWorld->removeRigidBody(allRigidBodies[i]);

	allRigidBodies.clear();

	delete dynamicsWorld;
}

void PhysicsWorld::SetGravity(float x, float y, float z)
{
	dynamicsWorld->setGravity(btVector3(0, 1.0, 0));

}

void PhysicsWorld::Update(float deltaS)
{
	dynamicsWorld->stepSimulation(deltaS, 10);
}


