#include "CollisionChecks.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\SphereCollider.h"

bool CollisionChecks::Collision(Collider* s, Collider* b)
{
	if (s->colliderType == Collider::BOX && b->colliderType == Collider::BOX)
		return Collision(dynamic_cast<BoxCollider*>(s), dynamic_cast<BoxCollider*>(b));

	else if (s->colliderType == Collider::BOX && b->colliderType == Collider::SPHERE)
		return Collision(dynamic_cast<SphereCollider*>(b),dynamic_cast<BoxCollider*>(s));

	else if (s->colliderType == Collider::SPHERE && b->colliderType == Collider::BOX)
		return Collision(dynamic_cast<SphereCollider*>(s), dynamic_cast<BoxCollider*>(b));

	else if (s->colliderType == Collider::SPHERE && b->colliderType == Collider::SPHERE)
		return Collision(dynamic_cast<SphereCollider*>(s), dynamic_cast<SphereCollider*>(b));	
}

bool CollisionChecks::Collision(SphereCollider* s, BoxCollider* b)
{
	glm::vec3 dist = glm::abs(s->transform.GetGlobalPosition() - b->transform.GetGlobalPosition());

	if (dist.x >= (b->transform.GetGlobalScale().x + s->transform.GetGlobalScale().x / 2)) { return false; }
	if (dist.y >= (b->transform.GetGlobalScale().y + s->transform.GetGlobalScale().x / 2)) { return false; }
	if (dist.z >= (b->transform.GetGlobalScale().z + s->transform.GetGlobalScale().x / 2)) { return false; }

	if (dist.x < (b->transform.GetGlobalScale().x / 2)) { return true; }
	if (dist.y < (b->transform.GetGlobalScale().y / 2)) { return true; }
	if (dist.z < (b->transform.GetGlobalScale().z / 2)) { return true; }

	float cornerDistance_sq = ((dist.x - b->transform.GetGlobalScale().x) * (dist.x - b->transform.GetGlobalScale().x)) +
		((dist.y - b->transform.GetGlobalScale().y) * (dist.y - b->transform.GetGlobalScale().y) +
		((dist.z - b->transform.GetGlobalScale().z) * (dist.z - b->transform.GetGlobalScale().z)));

	return (cornerDistance_sq < (s->transform.GetGlobalScale().x / 2 * s->transform.GetGlobalScale().x / 2));
	return 0;

}
bool CollisionChecks::Collision(SphereCollider* s, SphereCollider* b)
{
	float dist = glm::length2(s->transform.GetGlobalPosition() - b->transform.GetGlobalPosition());
	float sum = s->transform.GetGlobalScale().x + b->transform.GetGlobalScale().x;

	if (dist < (sum / 2) * (sum / 2))
		return 1;

	return 0;
}
bool CollisionChecks::Collision(BoxCollider* s, BoxCollider* b)
{
	if (s->transform.GetGlobalPosition().x + s->transform.GetGlobalScale().x  > b->transform.GetGlobalPosition().x - b->transform.GetGlobalScale().x  &&
		s->transform.GetGlobalPosition().x - s->transform.GetGlobalScale().x  < b->transform.GetGlobalPosition().x + b->transform.GetGlobalScale().x  &&
		s->transform.GetGlobalPosition().y + s->transform.GetGlobalScale().y  > b->transform.GetGlobalPosition().y - b->transform.GetGlobalScale().y  &&
		s->transform.GetGlobalPosition().y - s->transform.GetGlobalScale().y  < b->transform.GetGlobalPosition().y + b->transform.GetGlobalScale().y &&
		s->transform.GetGlobalPosition().z + s->transform.GetGlobalScale().z  > b->transform.GetGlobalPosition().z - b->transform.GetGlobalScale().z  &&
		s->transform.GetGlobalPosition().z - s->transform.GetGlobalScale().z  < b->transform.GetGlobalPosition().z + b->transform.GetGlobalScale().z)
		return 1;

	return 0;
}