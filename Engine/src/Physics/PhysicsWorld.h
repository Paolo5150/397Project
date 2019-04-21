#pragma once

#include "Bullet\btBulletCollisionCommon.h"
#include "Bullet\btBulletDynamicsCommon.h"
#include "Bullet\BulletCollision\CollisionShapes\btHeightfieldTerrainShape.h"
#include "..\Components\RigidBody.h"
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
private:


};