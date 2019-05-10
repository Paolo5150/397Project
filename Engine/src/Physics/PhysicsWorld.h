#pragma once

#include "Bullet\btBulletCollisionCommon.h"
#include "Bullet\btBulletDynamicsCommon.h"
#include "Bullet\BulletCollision\CollisionShapes\btHeightfieldTerrainShape.h"
#include "..\Components\RigidBody.h"
#include "Bullet\BulletCollision/CollisionDispatch/btCollisionObjectWrapper.h"
#include "Bullet\BulletCollision/CollisionDispatch/btCollisionObject.h"
#include "..\Utils\Quadtree.h"
#include <list>


class PhysicsWorld
{

public:
	static PhysicsWorld& Instance();
	PhysicsWorld();
	~PhysicsWorld();


	void Update(float deltaS);
	//void AddRigidBody(RigidBody* rb);
	void AddCollider(Collider* c);


	void InitializeQuadtree(int x, int y, int w, int h);
	void FillQuadtree(bool staticToo);

	static bool  CollisionCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1);
	std::vector<Collider*> allNonStaticColliders;
	std::vector<Collider*> allStaticColliders;

	QuadTree<Collider*>* nonStaticQuadtree;
	QuadTree<Collider*>* staticQuadtree;

	void PerformCollisions(bool staticToo);
private:
	void PerformCollisions(QuadNode<Collider*>* node);
};