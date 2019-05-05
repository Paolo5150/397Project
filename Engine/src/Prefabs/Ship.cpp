#include "Ship.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"

Ship::Ship() : GameObject("Ship")
{
	SetIsStatic(1);

	AssetLoader::Instance().GetAsset<Model>("Ship")->PopulateGameObject(this);
	transform.SetScale(20, 20, 20);

	Material mat_ship;
	mat_ship.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStatic"));
	mat_ship.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("shipTexture"));
	//mat_ship.LoadCubemap(&skybox->GetCubeMap());
	mat_ship.LoadFloat("shininess", 1000.0f);
	mat_ship.LoadFloat("reflectivness", 0.5f);

	ApplyMaterial(mat_ship);
}

void Ship::Start()
{
	BoxCollider* sc = new BoxCollider();
	sc->ResetCollisionLayer();
	sc->AddCollisionLayer(CollisionLayers::OBSTACLE);
	sc->ResetCollideAgainstLayer();
	sc->AddCollideAgainstLayer(CollisionLayers::PLAYER);
	sc->transform.SetScale(4, 4, 9);

	sc->transform.SetPosition(0, 5, 0);
	sc->enableRender = 1;
	AddComponent(sc);
}


Ship::~Ship()
{

}