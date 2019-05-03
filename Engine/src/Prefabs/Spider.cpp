#include "Spider.h"

Spider::Spider() : GameObject("Spider")
{
	AssetLoader::Instance().GetAsset<Model>("Spider")->PopulateGameObject(this);
	AddComponent(new AIBase("Assets\\Scripts\\AI"));
	AddComponent(new BoxCollider());
}

Spider::Spider(Transform& targetTransform) : GameObject("Spider")
{
	AssetLoader::Instance().GetAsset<Model>("Spider")->PopulateGameObject(this);
	AddComponent(new AIBase(targetTransform, "Assets\\Scripts\\AI"));
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