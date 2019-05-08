#include "Pumpkin.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"


Pumpkin::Pumpkin() : GameObject("Pumpkin")
{
	
	AssetLoader::Instance().GetAsset<Model>("Pumpkin")->PopulateGameObject(this);
	transform.SetScale(40, 40, 40);

}

void Pumpkin::Start()
{
	SphereCollider* sc = new SphereCollider();
	sc->ResetCollisionLayer();
	sc->ResetCollideAgainstLayer();
	sc->AddCollideAgainstLayer(CollisionLayers::PLAYER);
	sc->transform.SetScale(0.7, 0.7, 0.7);
	sc->transform.SetPosition(0, 0.2, 0);

	AddComponent(sc);
}


Pumpkin::~Pumpkin()
{

}