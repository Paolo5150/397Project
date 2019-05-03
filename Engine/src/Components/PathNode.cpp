#include "PathNode.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

PathNode::PathNode() : GameObject("PathNode")
{
	
	SetIsStatic(1);
}
PathNode::~PathNode()
{}


void PathNode::Start()
{
	BoxCollider* sc = new BoxCollider();
	sc->enableRender = 1;
	sc->ResetCollideAgainstLayer();
	sc->ResetCollisionLayer();

	sc->AddCollideAgainstLayer(CollisionLayers::OBSTACLE);
	sc->AddCollisionLayer(CollisionLayers::PATHNODE);

	sc->transform.SetScale(100, 100, 100);
	AddComponent(sc);
}

void PathNode::OnCollision(GameObject* go)
{
	//SetActive(0);
	GetComponent<BoxCollider>("BoxCollider")->meshRenderer->GetMaterial().SetColor(1, 0, 0);
	//Logger::LogInfo("Node collided against",go->GetName());
}
