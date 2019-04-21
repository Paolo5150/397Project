#pragma once

#include "Bullet\btBulletCollisionCommon.h"
#include "Bullet\btBulletDynamicsCommon.h"
#include "Bullet\BulletCollision\CollisionShapes\btHeightfieldTerrainShape.h"

class PhysicsWorld
{

public:
	PhysicsWorld();
	~PhysicsWorld();

	void SetGravity(float x, float y, float z);
	void Update(float deltaS);

private:
	btDynamicsWorld* dynamicsWorld;

};