#include "Spider.h"
#include "..\Components\AIBase.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\HealthComponent.h"
#include "Pumpkin.h"

namespace
{
	const float attackRate = 0.8;
}

Spider::Spider() : GameObject("Spider")
{
	AssetLoader::Instance().GetAsset<Model>("Spider")->PopulateGameObject(this);

	deathTimer = 0.0f;

	Material spiderMat;
	spiderMat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("Spinnen_Bein_tex_COLOR_"));
	spiderMat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultAnimated"));
	this->ApplyMaterial(spiderMat);

	aiBase = new AIBase("Assets\\Scripts\\AI\\Spider.lua");
	healthComponent = new HealthComponent(100, 100);
	AddComponent(healthComponent);

	AddComponent(aiBase);

}

Spider::Spider(float posX, float posY, float posZ) : GameObject("Spider")
{
	AssetLoader::Instance().GetAsset<Model>("Spider")->PopulateGameObject(this);

	deathTimer = 0.0f;

	Material spiderMat;
	spiderMat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("Spinnen_Bein_tex_COLOR_"));
	spiderMat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultAnimated"));
	this->ApplyMaterial(spiderMat);

	aiBase = new AIBase("Assets\\Scripts\\AI\\Spider.lua");

	AddComponent(aiBase);
	transform.SetPosition(posX, posY, posZ);
	healthComponent = new HealthComponent(100, 100);
	AddComponent(healthComponent);
}

Spider::Spider(Transform& g) : GameObject("Spider")
{

	AssetLoader::Instance().GetAsset<Model>("Spider")->PopulateGameObject(this);

	Material spiderMat;
	spiderMat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("Spinnen_Bein_tex_COLOR_"));
	spiderMat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultAnimated"));
	this->ApplyMaterial(spiderMat);

	aiBase = new AIBase("Assets\\Scripts\\AI\\Spider.lua");
	healthComponent = new HealthComponent(100, 100);
	AddComponent(healthComponent);
	AddComponent(aiBase);
}

Spider::Spider(Transform& g, float posX, float posY, float posZ) : GameObject("Spider")
{

	AssetLoader::Instance().GetAsset<Model>("Spider")->PopulateGameObject(this);

	Material spiderMat;
	spiderMat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("Spinnen_Bein_tex_COLOR_"));
	spiderMat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultAnimated"));
	this->ApplyMaterial(spiderMat);

	aiBase = new AIBase("Assets\\Scripts\\AI\\Spider.lua");
	healthComponent = new HealthComponent(100, 100);
	AddComponent(healthComponent);
	AddComponent(aiBase);
	transform.SetPosition(posX, posY, posZ);
}

Spider::~Spider()
{
}


void Spider::SetTarget(Transform& transform)
{
	aiBase->SetTarget(transform);
}


Transform* Spider::GetTarget() const
{
	return aiBase->GetTarget();
}

void Spider::Start()
{
	BoxCollider* sc = new BoxCollider();
	sc->ResetCollisionLayer();
	sc->AddCollisionLayer(CollisionLayers::ENEMY);
	sc->ResetCollideAgainstLayer();
	sc->AddCollideAgainstLayer(CollisionLayers::PUPMKIN);
	sc->transform.SetScale(80, 40, 80);

	sc->transform.SetPosition(0, 35, 0);
	AddComponent(sc);

	sc->collisionCallback = [this](GameObject* go) {


		if (go->GetName() == "Pumpkin")
		{
			Pumpkin* p = (Pumpkin*)go;
			if (p->state == Pumpkin::SHOT)
			{
				healthComponent->AddToHealth(-10);

				if (healthComponent->IsDead())
				{
					GetComponent<Animator>("Animator")->SetCurrentAnimation(1, false);
					aiBase->SetActive(false);
					aiBase->SetState("Dead");
					deathTimer = Timer::GetTimeS();
				}

				go->FlagToBeDestroyed();
			}
		}

	};
}

void Spider::Update()
{
	GameObject::Update(); //call base Update

	float h = Terrain::Instance().GetHeightAt(transform.GetPosition().x, transform.GetPosition().z);
	transform.SetPosition(transform.GetPosition().x, h, transform.GetPosition().z);

	//Logger::LogInfo("State", GetComponent<AIBase>("AIBase")->GetState());
	if (aiBase->GetState() == "Fight")
	{
		attackTimer += Timer::GetDeltaS();

		if (attackTimer >= attackRate)
		{
			attackTimer = 0;
			if (aiBase->GetTarget()->gameObject != nullptr)
			{
				HealthComponent* h = aiBase->GetTarget()->gameObject->GetComponent<HealthComponent>("HealthComponent");

				if (h != nullptr)
				{
					h->AddToHealth(-5);
				}
			}
		}
	}
	else if (aiBase->GetState() == "Dead")
	{
		if (Timer::GetTimeS() >= deathTimer + 1.8f)
		{
			FlagToBeDestroyed();
		}
	}
}

void Spider::OnCollision(GameObject* g)
{
	Logger::LogInfo("Spider hit by", g->GetName());
}
