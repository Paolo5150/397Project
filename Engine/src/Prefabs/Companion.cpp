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


	ApplyMaterial(mat);

	animator = GetComponent<Animator>("Animator");
	healthComponent = new HealthComponent(100, 100);
	transform.SetScale(0.05, 0.05, 0.05);
	AddComponent(healthComponent);
	attackDamage = 15;
	walkSpeed = 550;
	runSpeed = 800;
	currentSpeed = walkSpeed;
	
}

Companion::~Companion()
{

}

void Companion::Start()
{
	GameObject::Start();

	playerRef = SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Player")[0];
	currentState = IDLE_STATE;
}

void Companion::Update()
{
	GameObject::Update();



	if (healthComponent->IsDead() && currentState != DEAD_STATE)
	{
		ApplyColor(0.5, 0.5, 0.5);
		animator->stopPercentage = 0.5;
		currentState = DEAD_STATE;
	}


	switch (currentState)
	{
	case IDLE_STATE:
		animator->stopPercentage = 1;
		CheckForSpiders();
		Idle();
		break;
	case FOLLOW_STATE:
		animator->stopPercentage = 1;
		CheckForSpiders();
		FollowPlayer();
		break;
	case ATTACK_STATE:
		animator->stopPercentage = 1;
		Attack();
		break;
	case DEAD_STATE:
		Die();
		break;
	case CHARGE_STATE:
		animator->stopPercentage = 1;
		Charge();

	}
	
}

void Companion::Idle()
{
	animator->SetCurrentAnimation(ANIMATION::IDLE);
	glm::vec3 toTarget = glm::vec3(playerRef->transform.GetPosition().x, transform.GetPosition().y, playerRef->transform.GetPosition().z) - transform.GetPosition();
	if (glm::length(toTarget) > 250)
		currentState = FOLLOW_STATE;

}

void Companion::Attack()
{
	if (target == nullptr)
	{
		currentState = IDLE_STATE;
		return;
	}

	glm::vec3 toTarg = glm::vec3(target->transform.GetPosition().x, transform.GetPosition().y, target->transform.GetPosition().z) - transform.GetPosition();


	if (glm::length(toTarg) > 240)
		currentState = CHARGE_STATE;

	float yAngle = glm::angle(transform.GetLocalFront(), glm::normalize(toTarg));
	glm::vec3 cross = glm::cross(transform.GetLocalFront(), glm::normalize(toTarg));

	yAngle *= glm::sign(cross.y);
	if (abs(yAngle) > 0.1)
		transform.RotateBy(glm::degrees(yAngle), 0, 1, 0);
	animator->SetCurrentAnimation(ANIMATION::ATTACK);

	HealthComponent* hc = target->GetComponent<HealthComponent>("HealthComponent");

	static float timer = 0;
	timer += Timer::GetDeltaS();


	if (hc != nullptr)
	{
		if (timer > 1.0f)
		{
			timer = 0;
			hc->AddToHealth(-attackDamage);
			target->FlashColor(1, 0, 0);

			if (hc->IsDead())
			{
				target = nullptr;
				currentState = Companion::IDLE_STATE;
				return;
			}
		}
	}
	else
		currentState = Companion::IDLE_STATE;;

	if (Input::GetKeyPressed(GLFW_KEY_E))
	{
		currentState = Companion::IDLE_STATE;
	}

}

void Companion::Charge()
{
	
	if (Input::GetKeyPressed(GLFW_KEY_E) || target->GetName()=="Player")
	{
		currentState = Companion::FOLLOW_STATE;
	}

	currentSpeed = runSpeed;
	glm::vec3 toTarget = glm::vec3(target->transform.GetPosition().x, transform.GetPosition().y, target->transform.GetPosition().z) - transform.GetPosition();
	if (glm::length(toTarget) < 240)
		currentState = ATTACK_STATE;
	
	GoToTarget();

}


void Companion::SetTarget(GameObject* target)
{
	animator->SetCurrentAnimation(ANIMATION::RUN);
	currentState = CHARGE_STATE;
	currentSpeed = runSpeed;
	this->target = target;
	
}

void Companion::Die()
{
	animator->SetCurrentAnimation(ANIMATION::DEATH2,0);

}


void Companion::FollowPlayer()
{
	animator->SetCurrentAnimation(ANIMATION::WALK);	
	target = playerRef;
	currentSpeed = walkSpeed;
	GoToTarget();

	glm::vec3 toPlayer = glm::vec3(playerRef->transform.GetPosition().x, transform.GetPosition().y, playerRef->transform.GetPosition().z) - transform.GetPosition();
	if (glm::length(toPlayer) < 250)
		currentState = IDLE_STATE;
}

void Companion::GoToTarget()
{
	static float timer = 1;
	static glm::vec3 next;
	static glm::vec3 nextNode;

	timer += Timer::GetDeltaS();
	

	if (timer > 0.2f)
	{

		timer = 0;
		std::vector<glm::vec3> path = PathFinder::Instance().GeneratePath(transform.GetPosition(), target->transform.GetGlobalPosition());
		nextNode = path[0];

	}
	glm::vec3 toTarg = glm::vec3(nextNode.x, transform.GetPosition().y, nextNode.z) - transform.GetPosition();

	float yAngle = glm::angle(transform.GetLocalFront(), glm::normalize(toTarg));
	glm::vec3 cross = glm::cross(transform.GetLocalFront(), glm::normalize(toTarg));

	yAngle *= glm::sign(cross.y);
	if (abs(yAngle) > 0.1)
		transform.RotateBy(glm::degrees(yAngle), 0, 1, 0);

	glm::vec3  dir = glm::normalize(nextNode - transform.GetPosition()) * currentSpeed* Timer::GetDeltaS();
	next = transform.GetPosition() + dir;
	transform.SetPosition(next);

	float h = Terrain::Instance().GetHeightAt(transform.GetPosition().x, transform.GetPosition().z);
	transform.SetPosition(transform.GetPosition().x, h, transform.GetPosition().z);
}


void Companion::CheckForSpiders()
{
	static float checkSpidersTimer = 0;
	checkSpidersTimer += Timer::GetDeltaS();



	GameObject* closestSpider = nullptr;
	if (checkSpidersTimer > .4f)
	{

		checkSpidersTimer = 0;
		for (int i = 0; i < SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Enemy_Spider").size(); i++)
		{
			float dist = glm::length(SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Enemy_Spider")[i]->transform.GetGlobalPosition() - transform.GetGlobalPosition());
			closestSpider = dist < 300 ? SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Enemy_Spider")[i] : closestSpider;

		}
	}

	if (closestSpider != nullptr)
	{
		SetTarget(closestSpider);
	}

}