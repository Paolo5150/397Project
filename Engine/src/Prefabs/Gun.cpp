#include "Gun.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"

Gun::Gun() : GameObject("Gun")
{
	SetIsStatic(1);

	AssetLoader::Instance().GetAsset<Model>("Gun")->PopulateGameObject(this);
	transform.SetScale(0.8, 0.8, 0.8);
}

Gun::~Gun()
{

}