#include "Crate.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"

Crate::Crate() : GameObject("Crate")
{

	AssetLoader::Instance().GetAsset<Model>("Crate")->PopulateGameObject(this);
	transform.SetScale(8,8,8);

	Material mat_crate;
	mat_crate.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStaticNormalMap"));
	mat_crate.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("crate_diffuse"));
	mat_crate.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("crate_normal"), TextureUniform::NORMAL0);

	SetIsStatic(1);
	

	ApplyMaterial(mat_crate);
}

void Crate::Start()
{
	BoxCollider* sc = new BoxCollider();
	sc->ResetCollisionLayer();
	sc->AddCollisionLayer(CollisionLayers::OBSTACLE);
	sc->ResetCollideAgainstLayer();
	sc->AddCollideAgainstLayer(CollisionLayers::PLAYER);
	sc->transform.SetScale(8, 8, 8);
	sc->transform.SetPosition(0, 8, 0);
	sc->enableRender = 1;
	AddComponent(sc);
	Logger::LogError("Crate start");
}


Crate::~Crate()
{

}