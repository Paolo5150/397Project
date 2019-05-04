#include "PhysicsWorld.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\SphereCollider.h"



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
	//btBroadphaseInterface* broadphase = new btDbvtBroadphase();
	// Set up the collision configuration and dispatcher
	//btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	//btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	// The actual physics solver
	//btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
	// The world.
	//dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	//SetGravity(0.0f, -40.0f, 0.0f);

}

void PhysicsWorld::InitializeQuadtree(int x, int y, int w, int h)
{
	nonStaticQuadtree = new QuadTree<Collider*>(x, y, w, h);
	staticQuadtree = new QuadTree<Collider*>(x, y, w, h);

}

void PhysicsWorld::FillQuadtree(bool staticToo)
{
	nonStaticQuadtree->ClearNodes();


	for (unsigned i = 0; i < allNonStaticColliders.size(); i++)
	{
		nonStaticQuadtree->AddElement(allNonStaticColliders[i], allNonStaticColliders[i]->transform.GetGlobalPosition().x, allNonStaticColliders[i]->transform.GetGlobalPosition().z,
			allNonStaticColliders[i]->transform.GetGlobalScale().x, allNonStaticColliders[i]->transform.GetGlobalScale().z);
	}
	

	if (staticToo)
	{
		staticQuadtree->ClearNodes();

		for (unsigned i = 0; i < allStaticColliders.size(); i++)
		{
			staticQuadtree->AddElement(allStaticColliders[i], allStaticColliders[i]->transform.GetGlobalPosition().x, allStaticColliders[i]->transform.GetGlobalPosition().z,
				allStaticColliders[i]->transform.GetGlobalScale().x, allStaticColliders[i]->transform.GetGlobalScale().z);
		}

	}
}

PhysicsWorld::~PhysicsWorld()
{
	
	allRigidBodies.clear();
	delete dynamicsWorld;
	nonStaticQuadtree->ClearNodes();
	staticQuadtree->ClearNodes();
	delete nonStaticQuadtree;
	delete staticQuadtree;
}
/*
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
*/
void PhysicsWorld::AddCollider(Collider* rb)
{
	if (!rb->GetParent()->GetIsStatic())
		allNonStaticColliders.push_back(rb);
	else
	{

		allStaticColliders.push_back(rb);
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
	FillQuadtree(0);
	PerformCollisions(false);
	allNonStaticColliders.clear();
	/*auto it = allRigidBodies.begin();
	for (; it != allRigidBodies.end(); it++)
		(*it)->PrePhysicsUpdate();*/

	//dynamicsWorld->updateAabbs();
	//Logger::LogInfo("RB", allRigidBodies.size());
	//dynamicsWorld->stepSimulation(deltaS, 10);
}

bool PhysicsWorld::CollisionCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
{
	return false;
}

void PhysicsWorld::PerformCollisions(bool staticToo)
{
	PerformCollisions(nonStaticQuadtree->root);


	for (unsigned i = 0; i < allNonStaticColliders.size(); i++)
	{
		std::set<Collider*>& staticCols = staticQuadtree->GameObjectsAt(allNonStaticColliders[i]->transform.GetGlobalPosition().x, allNonStaticColliders[i]->transform.GetGlobalPosition().z);
		
		for (auto it = staticCols.begin(); it != staticCols.end(); it++)
		{
			if (allNonStaticColliders[i]->GetCollideAgainstLayer() & (*it)->GetCollisionLayer())
			{
				if (CollisionChecks::Collision(allNonStaticColliders[i], (*it)))
				{
					allNonStaticColliders[i]->collisionCallback((*it)->GetParent());
					(*it)->collisionCallback(allNonStaticColliders[i]->GetParent());
				}
			}
		}
		
	}

	if (staticToo)
	PerformCollisions(staticQuadtree->root);

	
	

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
		auto it = node->elements.begin();

		for (; it != node->elements.end(); it++)
		{
			auto it2 = node->elements.begin();

			for (; it2 != node->elements.end(); it2++)
			{
				if (*it == *it2) continue;
				if ((*it)->GetCollideAgainstLayer() & (*it2)->GetCollisionLayer())
				{
					if (CollisionChecks::Collision((*it), (*it2)))
					{
						(*it)->collisionCallback((*it2)->GetParent());
					}
				}
			}
		}
	}
}




