#include "PumpkinBunch.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"

namespace
{
	const float MAX_LIFETIME = 5;
}

PumpkinBunch::PumpkinBunch() : GameObject("PumpkinBunch")
{
	AssetLoader::Instance().GetAsset<Model>("PumpkinBunch")->PopulateGameObject(this);
	transform.SetScale(40, 40, 40);
	SetIsStatic(0);
}

void PumpkinBunch::Start()
{
	BoxCollider* sc = new BoxCollider();
	sc->ResetCollisionLayer();
	sc->AddCollisionLayer(CollisionLayers::PUPMKIN);
	sc->ResetCollideAgainstLayer();
	sc->AddCollideAgainstLayer(CollisionLayers::PLAYER);

	sc->transform.SetScale(0.55, 0.3, 0.55);
	sc->transform.SetPosition(0, 0.2, 0);
	//sc->enableRender = 1;

	AddComponent(sc);
}


PumpkinBunch::~PumpkinBunch()
{

}