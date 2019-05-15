#include "Tree.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"

Tree::Tree() : GameObject("Tree")
{
	AssetLoader::Instance().GetAsset<Model>("Tree")->PopulateGameObject(this);
	transform.SetScale(80, 80, 80);

	SetIsStatic(1);

}

void Tree::Start()
{
	BoxCollider* sc = new BoxCollider();
	sc->ResetCollisionLayer();
	sc->AddCollisionLayer(CollisionLayers::OBSTACLE);
	sc->ResetCollideAgainstLayer();
	sc->AddCollideAgainstLayer(CollisionLayers::PLAYER);
	sc->transform.SetScale(0.5, 2, 0.5);
	sc->transform.SetPosition(0, 1.5, 0);
	AddComponent(sc);

}


Tree::~Tree()
{

}