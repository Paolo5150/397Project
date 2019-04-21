#pragma once

#include "Bullet\btBulletCollisionCommon.h"
#include "Bullet\btBulletDynamicsCommon.h"
#include "Bullet\BulletCollision\CollisionShapes\btHeightfieldTerrainShape.h"
#include <vector>

class PhysicsWorld
{

public:
	static PhysicsWorld& Instance();
	PhysicsWorld();
	~PhysicsWorld();

	void SetGravity(float x, float y, float z);
	void Update(float deltaS);

	btDynamicsWorld* dynamicsWorld;
	std::vector<btRigidBody*> allRigidBodies;
private:


};