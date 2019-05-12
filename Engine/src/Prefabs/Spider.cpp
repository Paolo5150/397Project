#include "Spider.h"
#include "..\Components\AIBase.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\HealthComponent.h"
#include "Hive.h"
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

	AddComponent(aiBase);
	AddComponent(healthComponent);
}

Spider::Spider(float posX, float posY, float posZ) : GameObject("Spider")
{
	AssetLoader::Instance().GetAsset<Model>("Spider")->PopulateGameObject(this);

	deathTimer = 0.0f;

	transform.SetPosition(posX, posY, posZ);

	Material spiderMat;
	spiderMat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("Spinnen_Bein_tex_COLOR_"));
	spiderMat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultAnimated"));
	this->ApplyMaterial(spiderMat);

	aiBase = new AIBase("Assets\\Scripts\\AI\\Spider.lua");
	healthComponent = new HealthComponent(100, 100);

	AddComponent(aiBase);
	AddComponent(healthComponent);
}

Spider::Spider(Transform& g) : GameObject("Spider")
{

	AssetLoader::Instance().GetAsset<Model>("Spider")->PopulateGameObject(this);

	deathTimer = 0.0f;

	Material spiderMat;
	spiderMat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("Spinnen_Bein_tex_COLOR_"));
	spiderMat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultAnimated"));
	this->ApplyMaterial(spiderMat);

	aiBase = new AIBase("Assets\\Scripts\\AI\\Spider.lua");
	healthComponent = new HealthComponent(100, 100);

	AddComponent(aiBase);
	AddComponent(healthComponent);
}

Spider::Spider(Transform& g, float posX, float posY, float posZ) : GameObject("Spider")
{
	AssetLoader::Instance().GetAsset<Model>("Spider")->PopulateGameObject(this);

	deathTimer = 0.0f;

	transform.SetPosition(posX, posY, posZ);

	Material spiderMat;
	spiderMat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("Spinnen_Bein_tex_COLOR_"));
	spiderMat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultAnimated"));
	this->ApplyMaterial(spiderMat);

	aiBase = new AIBase("Assets\\Scripts\\AI\\Spider.lua");
	healthComponent = new HealthComponent(100, 100);

	AddComponent(aiBase);
	AddComponent(healthComponent);
}

Spider::~Spider()
{
	Hive::totalSpiders--;
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
	BoxCollider* slowCollider = new BoxCollider(); //Used for slowing down/stopping if touching another spider
	slowCollider->ResetCollisionLayer();
	slowCollider->AddCollisionLayer(CollisionLayers::SPIDER);
	slowCollider->ResetCollideAgainstLayer();
	slowCollider->AddCollideAgainstLayer(CollisionLayers::SPIDER);
	slowCollider->transform.SetScale(80, 40, 80);

	slowCollider->transform.SetPosition(0, 35, 0);
	AddComponent(slowCollider);

	slowCollider->collisionCallback = [this](GameObject* go) {

		if (go->GetName() == "Spider")
		{
			if ((((AIBase*)go->GetComponent<AIBase>("AIBase"))->GetState() == "Fight" || ((AIBase*)go->GetComponent<AIBase>("AIBase"))->GetState() == "Seek") && ((AIBase*)GetComponent<AIBase>("AIBase"))->GetState() != "Dead") //If the spider is colliding with a spider that is currently fighting, and this spider is not dead
				((AIBase*)GetComponent<AIBase>("AIBase"))->SetState("Slow"); //Tells the ai to slow down
		}
	};

	BoxCollider* pumpkinCollider = new BoxCollider(); //Used for when a pumpkin bullet hits the spider
	pumpkinCollider->ResetCollisionLayer();
	pumpkinCollider->AddCollisionLayer(CollisionLayers::ENEMY);
	pumpkinCollider->ResetCollideAgainstLayer();
	pumpkinCollider->AddCollideAgainstLayer(CollisionLayers::PUPMKIN);
	pumpkinCollider->transform.SetScale(80, 40, 80);

	pumpkinCollider->transform.SetPosition(0, 35, 0);
	AddComponent(pumpkinCollider);

	pumpkinCollider->collisionCallback = [this,pumpkinCollider,slowCollider](GameObject* go) {


		if (go->GetName() == "Pumpkin")
		{
			Pumpkin* p = (Pumpkin*)go;
			if (p->state == Pumpkin::SHOT)
			{
				healthComponent->AddToHealth(-10);

				if (healthComponent->IsDead())
				{
					pumpkinCollider->SetActive(0);
					slowCollider->SetActive(0);

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

	if (((AIBase*)GetComponent<AIBase>("AIBase"))->GetState() == "Slow")
		((AIBase*)GetComponent<AIBase>("AIBase"))->SetState(""); //Lets the ai pick a state again

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
			for (auto const& i : GetChildList()) //Hide all of the spider until it's cleaned up (doesn't seem to be working?)
			{
				i->GetComponentByType<MeshRenderer>("Renderer")->SetActive(false);
			}
			FlagToBeDestroyed();
		}
	}
}

void Spider::OnCollision(GameObject* g)
{
	Logger::LogInfo("Spider hit by", g->GetName());
}
