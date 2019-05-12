#include "Hive.h"
#include "..\Components\SphereCollider.h"
#include "..\Components\BoxCollider.h"
#include "..\Scene\Scene.h"
#include "..\Scene\SceneManager.h"
#include "..\Prefabs\Terrain.h"
#include "Spider.h"
#include "Player.h"

unsigned int Hive::totalSpiders = 0;

Hive::Hive() : GameObject("Hive")
{
	AssetLoader::Instance().GetAsset<Model>("Hive")->PopulateGameObject(this);
	transform.SetScale(100, 100, 100);

	Material mat_hive;
	mat_hive.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStaticNormalMap"));
	mat_hive.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("hive_diffuse"));
	mat_hive.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("hive_normal"), TextureUniform::NORMAL0);
	
	SetIsStatic(1);

	ApplyMaterial(mat_hive);

	_maxSpiders = 10;
}

Hive::Hive(int maxSpiders) : GameObject("Hive")
{
	AssetLoader::Instance().GetAsset<Model>("Hive")->PopulateGameObject(this);
	transform.SetScale(200, 200, 200);

	Material mat_hive;
	mat_hive.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStaticNormalMap"));
	mat_hive.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("hive_diffuse"));
	mat_hive.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("hive_normal"), TextureUniform::NORMAL0);

	SetIsStatic(1);

	ApplyMaterial(mat_hive);

	_maxSpiders = maxSpiders;
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
			break;
		case 1:
			_currentState = 1;
			GetChild("Hive_Normal")->GetComponentByType<MeshRenderer>("Renderer")->SetActive(false);
			GetChild("Hive_Damaged")->GetComponentByType<MeshRenderer>("Renderer")->SetActive(true);
			GetChild("Hive_Destroyed")->GetComponentByType<MeshRenderer>("Renderer")->SetActive(false);
			break;
		case 2:
			_currentState = 2;
			GetChild("Hive_Normal")->GetComponentByType<MeshRenderer>("Renderer")->SetActive(false);
			GetChild("Hive_Damaged")->GetComponentByType<MeshRenderer>("Renderer")->SetActive(false);
			GetChild("Hive_Destroyed")->GetComponentByType<MeshRenderer>("Renderer")->SetActive(true);
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
	sc->transform.SetScale(0.8, 0.8, 0.8);
	sc->transform.SetPosition(0, 1, 0);
	AddComponent(sc);

	SetState(0);
}

void Hive::Update()
{
	if ((GetState() == 0 || GetState() == 1) && totalSpiders < _maxSpiders && Timer::GetTimeS() >= _lastSpawnedSpider + 30.0f)
	{
		Spider* spider = new Spider();

		float angle = rand()*3.14159265359*2;
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

Hive::~Hive()
{

}