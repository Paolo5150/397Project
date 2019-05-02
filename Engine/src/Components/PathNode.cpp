#include "PathNode.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

PathNode::PathNode() : GameObject("PathNode")
{
	BoxCollider* sc = new BoxCollider();
	sc->enableRender = 1;
	sc->ResetCollideAgainstLayer();
	sc->ResetCollisionLayer();

	sc->AddCollideAgainstLayer(CollisionLayers::OBSTACLE);
	sc->AddCollisionLayer(CollisionLayers::PATHNODE);

	sc->transform.SetScale(50, 50, 50);
	AddComponent(sc);
	SetIsStatic(1);
}
PathNode::~PathNode()
{}

void PathNode::OnCollision(GameObject* go)
{
	SetActive(0);
	Logger::LogInfo("Node collided");
}
