#include "Spider.h"

Spider::Spider() : GameObject("Spider")
{
	AddComponent(new AIBase("Assets\\Scripts\\AI"));
	//AddComponent(new Animator());
	AddComponent(new BoxCollider());
}

Spider::Spider(Transform& targetTransform) : GameObject("Spider")
{
	AddComponent(new AIBase(targetTransform, "Assets\\Scripts\\AI"));
	AddComponent(new BoxCollider());
	AddComponent(new Animator(new AnimatedModel()));
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