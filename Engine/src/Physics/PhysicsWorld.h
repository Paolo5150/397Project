#pragma once

#include "Bullet\btBulletCollisionCommon.h"
#include "Bullet\btBulletDynamicsCommon.h"
#include "Bullet\BulletCollision\CollisionShapes\btHeightfieldTerrainShape.h"
#include "..\Components\RigidBody.h"
#include "Bullet\BulletCollision/CollisionDispatch/btCollisionObjectWrapper.h"
#include "Bullet\BulletCollision/CollisionDispatch/btCollisionObject.h"
#include <list>


class PhysicsWorld
{

public:
	static PhysicsWorld& Instance();
	PhysicsWorld();
	~PhysicsWorld();

	void SetGravity(float x, float y, float z);
	void Update(float deltaS);
	void AddRigidBody(RigidBody* rb);
	void RemoveRigidBody(RigidBody* rb);


	btDynamicsWorld* dynamicsWorld;
	std::vector<RigidBody*> allRigidBodies;

	static bool  CollisionCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1);
private:


};