#include "Pumpkin.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"

namespace
{
	const float MAX_LIFETIME = 5;
}

float Pumpkin::damageGiven = 25;

Pumpkin::Pumpkin() : GameObject("Pumpkin")
{
	
	AssetLoader::Instance().GetAsset<Model>("Pumpkin")->PopulateGameObject(this);
	transform.SetScale(40, 40, 40);
	state = GROUND;
	speed = 2000;
	SetIsStatic(0);

}

void Pumpkin::Start()
{
	BoxCollider* sc = new BoxCollider();
	sc->ResetCollisionLayer();
	sc->AddCollisionLayer(CollisionLayers::PUPMKIN);
	sc->ResetCollideAgainstLayer();
	sc->AddCollideAgainstLayer(CollisionLayers::PLAYER);

	sc->transform.SetScale(0.2,0.2,0.2);
	sc->transform.SetPosition(0, 0.2, 0);
	//sc->enableRender = 1;

	AddComponent(sc);
}


Pumpkin::~Pumpkin()
{


}

void Pumpkin::Update()
{
	GameObject::Update();
	if (state == SHOT)
	{

		lifeTimer += Timer::GetDeltaS();
		if (lifeTimer >= MAX_LIFETIME)
			FlagToBeDestroyed();

		glm::vec3 vel = shootDirection * speed * Timer::GetDeltaS();
		//Logger::LogInfo("Updating pumpking, pos", Maths::Vec3ToString(transform.GetPosition()));
		transform.SetPosition(transform.GetPosition() + vel);
	}
	else
	{



	}
}
