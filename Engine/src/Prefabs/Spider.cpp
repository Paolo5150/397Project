#include "Spider.h"

Spider::Spider(Transform& targetTransform) : GameObject("Spider")
{
	AddComponent(new AIBase(targetTransform));
	AddComponent(new BoxCollider());
}

Spider::~Spider()
{
}

void Spider::SetTarget(Transform& transform)
{
	GetComponent<AIBase>("AIBase")->SetTarget(transform);
}

Transform* Spider::GetTarget() const
{
	return GetComponent<AIBase>("AIBase")->GetTarget();
}