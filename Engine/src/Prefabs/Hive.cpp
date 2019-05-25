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


Hive::Hive() : GameObject("Hive")
{
	AssetLoader::Instance().GetAsset<Model>("Hive")->PopulateGameObject(this);
	transform.SetScale(100, 100, 100);

	Material mat_hive;
	mat_hive.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStaticNormalMap"));
	mat_hive.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("hive_diffuse"));
	mat_hive.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("hive_normal"), TextureUniform::NORMAL0);

	ApplyMaterial(mat_hive);

	_maxSpiders = 10;
	canSpawnSpiders = true;
	totalHives++;
}

Hive::Hive(int maxSpiders) : GameObject("Hive")
{
	AssetLoader::Instance().GetAsset<Model>("Hive")->PopulateGameObject(this);
	transform.SetScale(200, 200, 200);

	Material mat_hive;
	mat_hive.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStaticNormalMap"));
	mat_hive.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("hive_diffuse"));
	mat_hive.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("hive_normal"), TextureUniform::NORMAL0);

	ApplyMaterial(mat_hive);

	_maxSpiders = maxSpiders;
	canSpawnSpiders = true;

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
	healtthComponent = new HealthComponent(1000, 1000);
	AddComponent(healtthComponent);

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

	sc->collisionCallback = [this](GameObject* go)
	{
		if (go->GetName() == "Pumpkin")
		{
			go->FlagToBeDestroyed();
			healtthComponent->AddToHealth(-Pumpkin::GetDamageGiven());
			ApplyColor(0.8, 0.0, 0.0);
			colorTimer = 0.1f;
			redFlashing = 1;
		}
	};
	SetState(0);
}

void Hive::Update()
{
	colorTimer = colorTimer < 0 ? 0 : colorTimer - Timer::GetDeltaS();
	if (colorTimer == 0 && redFlashing)
	{
		ApplyColor(1, 1, 1);
		redFlashing = 0;
	}

	if (healtthComponent->GetHealthMaxRatio() < 0.7 && healtthComponent->GetHealthMaxRatio() > 0.4)
		SetState(1);
	else if (healtthComponent->GetHealthMaxRatio() <= 0.4)
		SetState(2);

	if (healtthComponent->IsDead())
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

Hive::~Hive()
{
	totalHives--;
}