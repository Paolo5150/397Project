#include "Companion.h"
#include "..\core\Input.h"
#include "..\Utils\PathFinder.h"
#include "..\Scene\Scene.h"
#include "Terrain.h"
#include "..\Scene\SceneManager.h"

int animIndex = 0;


Companion::Companion() : GameObject("Companion")
{
	AssetLoader::Instance().GetAsset<Model>("Alien")->PopulateGameObject(this);

	Material mat;
	mat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultAnimated"));
	mat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("white"));
	mat.SetColor(0.5, 0.5, 0.5);

	ApplyMaterial(mat);

	animator = GetComponent<Animator>("Animator");
	healthComponent = new HealthComponent(100, 100);
	transform.SetScale(0.05, 0.05, 0.05);
	AddComponent(healthComponent);
}

Companion::~Companion()
{

}

void Companion::Start()
{
	GameObject::Start();

	playerRef = SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Player")[0];

}

void Companion::Update()
{
	GameObject::Update();

	animator->SetCurrentAnimation(ANIMATION::WALK);

	static float timer = 1;
	static glm::vec3 next;
	static glm::vec3 nextNode;

	timer += Timer::GetDeltaS();
	
	if (timer > 0.5f)
	{
		timer = 0;
		std::vector<glm::vec3> path = PathFinder::Instance().GeneratePath(transform.GetPosition(), playerRef->transform.GetPosition());
		nextNode = path[0];

		Logger::LogInfo("Dir", Maths::Vec3ToString(transform.GetPosition()));
	}

	glm::vec3  dir = glm::normalize(nextNode - transform.GetPosition()) * 400.0f * Timer::GetDeltaS();
	next = transform.GetPosition() + dir;

	transform.SetPosition(next);

	float h = Terrain::Instance().GetHeightAt(transform.GetPosition().x, transform.GetPosition().z);
	transform.SetPosition(transform.GetPosition().x,h,transform.GetPosition().z);
}