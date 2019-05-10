#include "Spider.h"
#include "..\Components\AIBase.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\HealthComponent.h"

namespace
{
	const float attackRate = 0.8;
}

Spider::Spider() : GameObject("Spider")
{
	AssetLoader::Instance().GetAsset<Model>("Spider")->PopulateGameObject(this);
	
	Material spiderMat;
	spiderMat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("Spinnen_Bein_tex_COLOR_"));
	spiderMat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultAnimated"));
	this->ApplyMaterial(spiderMat);

	aiBase = new AIBase("Assets\\Scripts\\AI\\Spider.lua");

	AddComponent(aiBase);
}

Spider::Spider(float posX, float posY, float posZ) : GameObject("Spider")
{
	AssetLoader::Instance().GetAsset<Model>("Spider")->PopulateGameObject(this);
	
	Material spiderMat;
	spiderMat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("Spinnen_Bein_tex_COLOR_"));
	spiderMat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultAnimated"));
	this->ApplyMaterial(spiderMat);

	aiBase = new AIBase("Assets\\Scripts\\AI\\Spider.lua");

	AddComponent(aiBase);
	transform.SetPosition(posX, posY, posZ);
}

Spider::Spider(Transform& g) : GameObject("Spider")
{

	AssetLoader::Instance().GetAsset<Model>("Spider")->PopulateGameObject(this);

	Material spiderMat;
	spiderMat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("Spinnen_Bein_tex_COLOR_"));
	spiderMat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultAnimated"));
	this->ApplyMaterial(spiderMat);

	aiBase = new AIBase("Assets\\Scripts\\AI\\Spider.lua");

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
}

void Spider::OnCollision(GameObject* g)
{
	Logger::LogInfo("Spider hit by", g->GetName());
}
