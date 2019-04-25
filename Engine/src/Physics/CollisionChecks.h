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
	static bool getSeparatingPlane(glm::vec3 RPos, glm::vec3 Plane, BoxCollider* box1, BoxCollider* box2);

	static bool CollisionChecks::getCollision(BoxCollider* box1, BoxCollider* box2);


};