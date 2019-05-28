#include "Hive.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"
#include "..\Scene\Scene.h"
#include "..\Scene\SceneManager.h"
#include "..\Prefabs\Terrain.h"
#include "..\Event\EventDispatcher.h"
#include "..\Event\AIEvents.h"
#include "..\Prefabs\Pumpkin.h"

#include "Spider.h"
#include "Player.h"


unsigned int Hive::totalHives = 0;


Hive::Hive() : GameObject("Hive"), Saveable()
{
	AssetLoader::Instance().GetAsset<Model>("Hive")->PopulateGameObject(this);
	transform.SetScale(100, 100, 100);

	healthComponent = new HealthComponent(1000, 1000);
	AddComponent(healthComponent);

	Material mat_hive;
	mat_hive.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStaticNormalMap"));
	mat_hive.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("hive_diffuse"));
	mat_hive.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("hive_normal"), TextureUniform::NORMAL0);

	ApplyMaterial(mat_hive);

	_maxSpiders = 15;
	canSpawnSpiders = true;
	totalHives++;

	SetState(0);
}

Hive::Hive(int maxSpiders) : GameObject("Hive"), Saveable()
{
	AssetLoader::Instance().GetAsset<Model>("Hive")->PopulateGameObject(this);
	transform.SetScale(200, 200, 200);

	healthComponent = new HealthComponent(1000, 1000);
	AddComponent(healthComponent);

	Material mat_hive;
	mat_hive.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStaticNormalMap"));
	mat_hive.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("hive_diffuse"));
	mat_hive.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("hive_normal"), TextureUniform::NORMAL0);

	ApplyMaterial(mat_hive);

	_maxSpiders = maxSpiders;
	canSpawnSpiders = true;
	totalHives++;

	SetState(0);
}

void Hive::SetMaxSpiders(unsigned int maxSpiders)
{
	_maxSpiders = maxSpiders;
}

unsigned int Hive::GetMaxSpiders() const
{
	return _maxSpiders;
}

void Hive::SetState(unsigned int index)
{
	switch (index)
	{
		case 0:
			_currentState = 0;
			GetChild("Hive_Normal")->GetComponentByType<MeshRenderer>("Renderer")->SetActive(true);
			GetChild("Hive_Damaged")->GetComponentByType<MeshRenderer>("Renderer")->SetActive(false);
			GetChild("Hive_Destroyed")->GetComponentByType<MeshRenderer>("Renderer")->SetActive(false);
			canSpawnSpiders = true;
			break;
		case 1:
			_currentState = 1;
			GetChild("Hive_Normal")->GetComponentByType<MeshRenderer>("Renderer")->SetActive(false);
			GetChild("Hive_Damaged")->GetComponentByType<MeshRenderer>("Renderer")->SetActive(true);
			GetChild("Hive_Destroyed")->GetComponentByType<MeshRenderer>("Renderer")->SetActive(false);
			canSpawnSpiders = true;
			break;
		case 2:
			_currentState = 2;
			GetChild("Hive_Normal")->GetComponentByType<MeshRenderer>("Renderer")->SetActive(false);
			GetChild("Hive_Damaged")->GetComponentByType<MeshRenderer>("Renderer")->SetActive(false);
			GetChild("Hive_Destroyed")->GetComponentByType<MeshRenderer>("Renderer")->SetActive(true);
			canSpawnSpiders = true;
			break;
		default:
			Logger::LogWarning("Attempted to set invalid Hive State!");
			break;
	}

}

unsigned int Hive::GetState() const
{
	return _currentState;
}

void Hive::Start()
{
	BoxCollider* sc = new BoxCollider();
	sc->ResetCollisionLayer();
	sc->AddCollisionLayer(CollisionLayers::OBSTACLE);

	sc->ResetCollideAgainstLayer();
	sc->AddCollideAgainstLayer(CollisionLayers::PLAYER);
	sc->AddCollideAgainstLayer(CollisionLayers::PUPMKIN);


	//sc->enableRender = 1;
	sc->transform.SetScale(0.6, 0.6, 0.6);
	sc->transform.SetPosition(0, 0.6, 0);
	AddComponent(sc);

	// Callback needs to be specified after adding the component
	sc->collisionCallback = [this](GameObject* go)
	{
		if (go->GetName() == "Pumpkin")
		{
			go->FlagToBeDestroyed();
			healthComponent->AddToHealth(-Pumpkin::GetDamageGiven());
			EventDispatcher::Instance().DispatchEvent(new EnemySpottedEvent());
			FlashColor(1, 0, 0);
		}
	};
}

void Hive::Update()
{
	GameObject::Update();
	

	if (healthComponent->GetHealthMaxRatio() < 0.7 && healthComponent->GetHealthMaxRatio() > 0.4)
		SetState(1);
	else if (healthComponent->GetHealthMaxRatio() <= 0.4)
		SetState(2);

	if (healthComponent->IsDead())
		FlagToBeDestroyed();

	if (canSpawnSpiders)
	{
		if (Spider::GetTotalSpiders() < _maxSpiders && Timer::GetTimeS() >= _lastSpawnedSpider + 15.0f) //Spawns spider only if the maximum spiders has not been reached and if a set amount of time has elapsed
		{
			Spider* spider = new Spider();

			//Spawn spiders in a circle around hive (not sure if this is working)
			float angle = rand()*3.14159265359 * 2;
			float r = 50;
			float spiderX = transform.GetPosition().x + r * cos(angle);
			float spiderZ = transform.GetPosition().z + r * sin(angle);

			spider->SetTarget(((Player*)SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Player").at(0))->transform);
			spider->transform.SetPosition(spiderX, Terrain::Instance().GetHeightAt(spiderX, spiderZ), spiderZ);
			spider->Start();
			SceneManager::Instance().GetCurrentScene().AddGameObject(spider);
			_lastSpawnedSpider = Timer::GetTimeS();
		}
	}
}

std::string Hive::Save()
{
	std::ostringstream ss;
	ss << "Hive" << "\n"
		<< transform.GetPosition().x << "\n"
		<< transform.GetPosition().y << "\n"
		<< transform.GetPosition().z << "\n"
		<< healthComponent->GetCurrentHealth() << "\n"
		<< GetState() << "\n"
		<< "end" << "\n";
	return (ss.str());
}

Hive::~Hive()
{
	totalHives--;
}