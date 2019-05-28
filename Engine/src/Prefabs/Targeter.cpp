#include "Targeter.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"
#include "..\Scene\Scene.h"
#include "..\Scene\SceneManager.h"
#include "Companion.h"

namespace
{
	const float MAX_LIFETIME = 5;
}



Targeter::Targeter() : GameObject("Targeter")
{
	AssetLoader::Instance().GetAsset<Model>("Bone")->PopulateGameObject(this);

	Material mat;
	mat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStatic"));
	mat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("white"));
	ApplyMaterial(mat);
	transform.SetScale(30,30,30);

	speed = 10000;
	SetIsStatic(0);

}

void Targeter::Start()
{
	companionRef = dynamic_cast<Companion*>( SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Companion")[0]);
	BoxCollider* sc = new BoxCollider();
	sc->transform.SetScale(0.2, 0.2, 0.2);
	sc->transform.SetRotation(0, 0, 0);
	sc->ResetCollisionLayer();
	sc->AddCollisionLayer(CollisionLayers::PUPMKIN);
	sc->ResetCollideAgainstLayer();
	sc->AddCollideAgainstLayer(CollisionLayers::OBSTACLE);
	sc->AddCollideAgainstLayer(CollisionLayers::SPIDER);
	AddComponent(sc);

	// Callback needs to be specified after adding the component
	sc->collisionCallback = [this](GameObject* go){
	
		companionRef->SetTarget(go);
		go->FlashColor(0, 1, 1);
		FlagToBeDestroyed();
	};


}


Targeter::~Targeter()
{


}

void Targeter::Update()
{
	GameObject::Update();


	lifeTimer += Timer::GetDeltaS();
	if (lifeTimer >= MAX_LIFETIME)
		FlagToBeDestroyed();

	glm::vec3 vel = shootDirection * speed * Timer::GetDeltaS();

	transform.SetPosition(transform.GetPosition() + vel);

}
