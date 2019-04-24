#pragma once

class BoxCollider;
class SphereCollider;
class Collider;

class CollisionChecks
{
public:
	static bool Collision(Collider* s, Collider* b);
private:
	static bool Collision(SphereCollider* s, BoxCollider* b);
	static bool Collision(SphereCollider* s, SphereCollider* b);
	static bool Collision(BoxCollider* s, BoxCollider* b);


};