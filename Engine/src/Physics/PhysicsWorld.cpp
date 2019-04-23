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
	SetGravity(0.0f, -40.0f, 0.0f);
	

}

void PhysicsWorld::InitializeQuadtree(int x, int y, int w, int h)
{
	quadtree = new QuadTree<Collider*>(x, y, w, h);
}

void PhysicsWorld::FillQuadtree()
{
	quadtree->ClearNodes();
	auto it = allColliders.begin();

	for (; it != allColliders.end(); it++)
	{
		quadtree->AddElement((*it), (*it)->transform.GetGlobalPosition().x, (*it)->transform.GetGlobalPosition().z);
	}
}

PhysicsWorld::~PhysicsWorld()
{
	
	allRigidBodies.clear();
	delete dynamicsWorld;
	quadtree->ClearNodes();
	delete quadtree;
}

void PhysicsWorld::AddRigidBody(RigidBody* rb)
{
	bool found = 0;

	auto it = allRigidBodies.begin();

	for (; it != allRigidBodies.end() && !found; it++)
	{
		if ((*it) == rb)
			found = 1;
	}

	if (!found)
	{
		allRigidBodies.push_back(rb);
		dynamicsWorld->addRigidBody(rb->btrb);
	}
}

void PhysicsWorld::AddCollider(Collider* rb)
{
	bool found = 0;

	auto it = allColliders.begin();

	for (; it != allColliders.end() && !found; it++)
	{
		if ((*it) == rb)
			found = 1;
	}

	if (!found)
	{
		allColliders.push_back(rb);
	}
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

	/*auto it = allRigidBodies.begin();
	for (; it != allRigidBodies.end(); it++)
		(*it)->PrePhysicsUpdate();*/

	//dynamicsWorld->updateAabbs();
	//Logger::LogInfo("RB", allRigidBodies.size());
	//dynamicsWorld->stepSimulation(deltaS, 10);
}

bool PhysicsWorld::CollisionCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
{
	Logger::LogInfo("Collision");
	return false;
}

void PhysicsWorld::PerformCollisions()
{

}

void PhysicsWorld::PerformCollisions(QuadNode<Collider*>* node)
{
	if (node->isSplit)
	{
		PerformCollisions(node->topLeft);
		PerformCollisions(node->topRight);
		PerformCollisions(node->bottomLeft);
		PerformCollisions(node->bottomRight);
	}
	else
	{
		auto it = node->gameObjects.begin();

		for (; it != node->gameObjects.end(); it++)
		{
			auto it2 = node->gameObjects.begin();

			for (; it2 != node->gameObjects.end(); it2++)
			{
				
			}
		}
	}
}




