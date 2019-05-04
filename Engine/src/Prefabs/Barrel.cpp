#include "Barrel.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"

Barrel::Barrel() : GameObject("Barrel")
{

	AssetLoader::Instance().GetAsset<Model>("Barrel")->PopulateGameObject(this);
	transform.SetScale(80, 80, 80);
	SetIsStatic(1);

}

void Barrel::Start()
{
	BoxCollider* sc = new BoxCollider();
	sc->ResetCollisionLayer();
	sc->AddCollisionLayer(CollisionLayers::OBSTACLE);
	sc->ResetCollideAgainstLayer();
	sc->AddCollideAgainstLayer(CollisionLayers::PLAYER);
	sc->transform.SetScale(0.5, 0.7, 0.5);
	sc->transform.SetPosition(0, 0.7, 0);
	sc->enableRender = 1;
	AddComponent(sc);
}


Barrel::~Barrel()
{

}