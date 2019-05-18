#include "GranadeLauncher.h"
#include "..\Components\MeshRenderer.h"
GranadeLauncher::GranadeLauncher() : GameObject("GranadeLauncher")
{
	AssetLoader::Instance().GetAsset<Model>("GranadeLauncher")->PopulateGameObject(this);
	transform.SetScale(2, 2, 2);

	Material mat_crate;
	mat_crate.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStatic"));
	mat_crate.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("launcher"));
	
	GetChild("GrenadeLauncherToon1")->GetComponent<MeshRenderer>("MeshRenderer")->SetIsCullable(false);
	SetLayer(0);
	SetLayer(Layers::GUN);



	ApplyMaterial(mat_crate);
}

void GranadeLauncher::Start()
{
	boxCollider = new BoxCollider();
	boxCollider->ResetCollisionLayer();
	boxCollider->AddCollisionLayer(CollisionLayers::LAUNCHER);
	boxCollider->ResetCollideAgainstLayer();
	boxCollider->AddCollideAgainstLayer(CollisionLayers::PLAYER);
	boxCollider->transform.SetScale(0.2, 0.2, 0.2);
	boxCollider->transform.SetPosition(0, 0.2, 0);


	AddComponent(boxCollider);
}


GranadeLauncher::~GranadeLauncher()
{

}