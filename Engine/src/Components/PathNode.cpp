#include "PathNode.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

PathNode::PathNode() : GameObject("PathNode")
{
	
	SetIsStatic(1);
	distanceFromPrevious = 0;
	distanceFromTarget = 0;
	cost = 0;
}
PathNode::~PathNode()
{
}


void PathNode::Start()
{
	sc = new BoxCollider();

	sc->ResetCollideAgainstLayer();
	sc->ResetCollisionLayer();

	sc->AddCollideAgainstLayer(CollisionLayers::OBSTACLE);

	sc->AddCollisionLayer(CollisionLayers::PATHNODE);

	sc->transform.SetScale(100, 100, 100);
	cost = 0;
	AddComponent(sc);
}

void PathNode::Update()
{

}

void PathNode::EngineUpdate()
{
	GameObject::EngineUpdate();
}

void PathNode::LateUpdate()
{

}

void PathNode::OnCollision(GameObject* go)
{
	//SetActive(0);
	GetComponent<BoxCollider>("BoxCollider")->meshRenderer->GetMaterial().SetColor(1, 0, 0);
	cost = 1000;
	//Logger::LogInfo("Node collided against",go->GetName());
}


