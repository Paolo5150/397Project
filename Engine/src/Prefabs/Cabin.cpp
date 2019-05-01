#include "Cabin.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"

Cabin::Cabin() : GameObject("Cabin")
{

	AssetLoader::Instance().GetAsset<Model>("Cabin")->PopulateGameObject(this);
	transform.SetScale(50, 50, 50);

	transform.SetRotation(-90, 0, 0);
	BoxCollider* sc = new BoxCollider();
	sc->ResetCollisionLayer();
	sc->AddCollisionLayer(CollisionLayers::OBSTACLE);
	sc->ResetCollideAgainstLayer();
	sc->AddCollideAgainstLayer(CollisionLayers::PLAYER);
	sc->transform.SetScale(1,1,2.2);

	sc->transform.SetPosition(0, 0.0, 1);
	sc->enableRender = 1;
	AddComponent(sc);

	Material mat_cabin;
	mat_cabin.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStaticNormalMap"));
	mat_cabin.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("cabin_diffuse"));
	mat_cabin.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("cabin_normal"), TextureUniform::NORMAL0);

	ApplyMaterial(mat_cabin);
}

Cabin::~Cabin()
{

}