#include "Spider.h"
#include "..\Components\AIBase.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\HealthComponent.h"
#include "..\Event\EventDispatcher.h"
#include "..\Event\AIEvents.h"
#include "Hive.h"
#include "..\GUI\GUIElements\GUIManager.h"
#include "..\Scene\SceneManager.h"
#include "..\Scene\Scene.h"

#include "Pumpkin.h"
#include "Companion.h"
#include "PLayer.h"


namespace
{
	const float attackRate = 0.5;
}

unsigned Spider::totalSpiders = 0;
unsigned Spider::totalSpidersKilled = 0;


Spider::Spider() : GameObject("Enemy_Spider"), Saveable()
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

	_enemySpottedEventID = EventDispatcher::Instance().SubscribeCallback<EnemySpottedEvent>(std::bind(&Spider::EnemySpotted, this, std::placeholders::_1));
}

Spider::Spider(float posX, float posY, float posZ) : GameObject("Enemy_Spider"), Saveable()
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

	_enemySpottedEventID = EventDispatcher::Instance().SubscribeCallback<EnemySpottedEvent>(std::bind(&Spider::EnemySpotted, this, std::placeholders::_1));
}

Spider::Spider(Transform& g) : GameObject("Enemy_Spider"), Saveable()
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

	_enemySpottedEventID = EventDispatcher::Instance().SubscribeCallback<EnemySpottedEvent>(std::bind(&Spider::EnemySpotted, this, std::placeholders::_1));
}

Spider::Spider(Transform& g, float posX, float posY, float posZ) : GameObject("Enemy_Spider"), Saveable()
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

	_enemySpottedEventID = EventDispatcher::Instance().SubscribeCallback<EnemySpottedEvent>(std::bind(&Spider::EnemySpotted, this, std::placeholders::_1));
}

Spider::~Spider()
{
	totalSpiders--;
	totalSpidersKilled++;
	EventDispatcher::Instance().UnsubscribeCallback<EnemySpottedEvent>(_enemySpottedEventID);
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
	GameObject::Start();
	totalSpiders++;
	
	companion = dynamic_cast<Companion*>(SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Companion")[0]);
	player = dynamic_cast<Player*>(SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Player")[0]);


	
	slowCollider = new BoxCollider(); //Used for slowing down/stopping if touching another spider
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

	pumpkinCollider = new BoxCollider(); //Used for when a pumpkin bullet hits the spider
	pumpkinCollider->ResetCollisionLayer();
	pumpkinCollider->AddCollisionLayer(CollisionLayers::ENEMY);
	pumpkinCollider->ResetCollideAgainstLayer();
	pumpkinCollider->AddCollideAgainstLayer(CollisionLayers::PUPMKIN);
	pumpkinCollider->transform.SetScale(80, 40, 80);

	pumpkinCollider->transform.SetPosition(0, 35, 0);
	AddComponent(pumpkinCollider);

	pumpkinCollider->collisionCallback = [this](GameObject* go) {


		if (go->GetName() == "Pumpkin")
		{
			Pumpkin* p = (Pumpkin*)go;
			if (p->state == Pumpkin::SHOT)
			{
				healthComponent->AddToHealth(-Pumpkin::GetDamageGiven());

				FlashColor(1, 0, 0);
				

				go->FlagToBeDestroyed();
			}
		}

	};


}

void Spider::Update()
{

	GameObject::Update(); //call base Update

	float toPlayer = glm::length(player->transform.GetPosition() - transform.GetPosition());
	float toComp = glm::length(companion->transform.GetPosition() - transform.GetPosition());

	if (companion->GetHealthComponent()->IsDead())
		SetTarget(player->transform);
	else
	{
		if (toPlayer < toComp)
			SetTarget(player->transform);

		else
			SetTarget(companion->transform);

	}


	if (healthComponent->IsDead() && aiBase->GetState() != "Dead")
	{
		pumpkinCollider->SetActive(0);
		slowCollider->SetActive(0);

		GetComponent<Animator>("Animator")->SetCurrentAnimation(1, false);
		aiBase->SetActive(false);
		aiBase->SetState("Dead");
		deathTimer = Timer::GetTimeS();
	}


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
					aiBase->GetTarget()->gameObject->FlashColor(1, 0, 0);
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

	// Limit spider's position within terrain
	if (transform.GetPosition().x > Terrain::Instance().GetTerrainMaxX() - 1500)
		transform.SetPosition(Terrain::Instance().GetTerrainMaxX() - 1500, transform.GetPosition().y, transform.GetPosition().z);
	else if (transform.GetPosition().x < Terrain::Instance().GetTerrainMinX() + 1500)
		transform.SetPosition(Terrain::Instance().GetTerrainMinX() + 1500, transform.GetPosition().y, transform.GetPosition().z);

	if (transform.GetPosition().z > Terrain::Instance().GetTerrainMaxZ() - 1500)
		transform.SetPosition(transform.GetPosition().x, transform.GetPosition().y, Terrain::Instance().GetTerrainMaxZ() - 1500);
	if (transform.GetPosition().z < Terrain::Instance().GetTerrainMinZ() + 1500)
		transform.SetPosition(transform.GetPosition().x, transform.GetPosition().y, Terrain::Instance().GetTerrainMinZ() + 1500);

	if (transform.GetPosition().y < 750)
	{
		underwaterTimer += Timer::GetDeltaS();

		if (underwaterTimer > 3)
			healthComponent->AddToHealth(Timer::GetDeltaS() * -3);
	}
	else
		underwaterTimer = 0;
}

std::string Spider::Save()
{
	std::ostringstream ss;
	ss << "Spider" << "\n"
		<< transform.GetPosition().x << "\n"
		<< transform.GetPosition().y << "\n"
		<< transform.GetPosition().z << "\n"
		//<< transform.GetRotation().x << "\n"
		//<< transform.GetRotation().y << "\n"
		//<< transform.GetRotation().z << "\n"
		<< healthComponent->GetCurrentHealth() << "\n"
		<< "end" << "\n";
	return (ss.str());
}

bool Spider::EnemySpotted(Event* e)
{
	aiBase->SetEventReceived(true);

	return 0;
}

void Spider::OnCollision(GameObject* g)
{
	Logger::LogInfo("Spider hit by", g->GetName());
}
