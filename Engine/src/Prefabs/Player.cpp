#include "Player.h"
#include "..\Scene\Scene.h"
#include "..\Scene\SceneManager.h"

#include "Terrain.h"
#include "Pumpkin.h"

namespace {

	const float MIN_SPEED = 0;
	const float MAX_SPEED = 1000;
	float ORIGINAL_SPEED = 500;
	float counter = 0;
	float SHOOT_RATE = 0.1;

	CameraPerspective* gunCam;
}


Player::Player() : GameObject("Player")
{
	mainCamera = new MainCamera();
	_movementSpeed = 20;
	_rotationSpeed = 20;
	_isTopView = false;
	_intendedDir = glm::vec3(0, 0, 0);
	ammoCounter = 10;

	gn = new GranadeLauncher();



	gunCam = new CameraPerspective(60.0f, Window::Instance().GetAspectRatio(), 0.1f, 10000.0f);
	gunCam->RemoveAllMaskLayers();
	gunCam->AddLayerMask(Layers::GUN);
	gunCam->SetDepth(10);
	gunCam->SetIsStatic(0);



}

void Player::OnAddToScene(Scene& theScene)
{
	GameObject::OnAddToScene(theScene);
	theScene.AddGameObject(mainCamera);
	theScene.AddGameObject(gunCam);

}



Player::~Player() {}

void Player::Start()
{
	GameObject::Start();
	//int x, y, z;
	//Terrain::Instance().GetCenter(x, y, z);
	//transform.SetPosition(x, y, z);
	transform.SetRotation(0, 0, 0);

	boxCollider = new BoxCollider();
	AddComponent(boxCollider); // Needs to be added first and modified later. I know, messy
	boxCollider->transform.SetScale(10, 60, 10);
	boxCollider->meshRenderer->SetIsCullable(0);
	boxCollider->ResetCollisionLayer();
	boxCollider->AddCollisionLayer(CollisionLayers::PLAYER);
	boxCollider->AddCollideAgainstLayer(CollisionLayers::OBSTACLE);
	boxCollider->AddCollideAgainstLayer(CollisionLayers::ENEMY);


	//boxCollider->enableRender = 1;
	boxCollider->transform.parent = nullptr;
	boxCollider->collisionCallback = [this](GameObject* go) {
		_movementSpeed = 0;
	};

	pickupCollider = new BoxCollider();
	AddComponent(pickupCollider); // Needs to be added first and modified later. I know, messy
	pickupCollider->transform.SetScale(10, 60, 10);
	pickupCollider->meshRenderer->SetIsCullable(0);
	pickupCollider->ResetCollisionLayer();
	//pickupCollider->enableRender = 1;
	pickupCollider->AddCollideAgainstLayer(CollisionLayers::PUPMKIN);
	pickupCollider->collisionCallback = [this](GameObject* go) {

		if (go->GetName() == "Pumpkin")
		{
			Pumpkin* p = (Pumpkin*)go;
			if (p->state == Pumpkin::GROUND)
			{

				ammoCounter++;
				go->FlagToBeDestroyed();
			}
		}
		else if (go->GetName() == "PumpkinBunch")
		{
			ammoCounter += 3;
			go->FlagToBeDestroyed();
		}

	};


	gn->transform.SetScale(0.01, 0.01, 0.01);
	gn->transform.SetPosition(-0.899999, -1.96, 3.68);
	gunCam->AddChild(gn);

	healhComponent = new HealthComponent(100, 100);
	AddComponent(healhComponent);

}






void Player::Update()
{
	GameObject::Update();
	_intendedDir.x = 0;
	_intendedDir.y = 0;
	_intendedDir.z = 0;

	//Logger::LogInfo(gn->transform.ToString());
	if (Input::GetMouseDown(0) && ammoCounter > 0)
	{
		shootTimer += Timer::GetDeltaS();
		if (shootTimer >= SHOOT_RATE)
		{
			shootTimer = 0;
			Pumpkin* pump = new Pumpkin();
			pump->transform.SetPosition(transform.GetPosition() + transform.GetLocalFront() * 80.0f - transform.GetLocalUp() * 10.0f);
			pump->Start();
			pump->state = Pumpkin::SHOT;
			pump->shootDirection = transform.GetLocalFront();
			SceneManager::Instance().GetCurrentScene().AddGameObject(pump);
			ammoCounter--;

		}
	}
	else
		shootTimer = SHOOT_RATE;


	UpdateControls();


	float h = Terrain::Instance().GetHeightAt(transform.GetPosition().x, transform.GetPosition().z);
	transform.SetPosition(transform.GetPosition().x, h + 60, transform.GetPosition().z);

	// Limit camera position within terrain
	if (transform.GetPosition().x > Terrain::Instance().GetTerrainMaxX() - 1500)
		transform.SetPosition(Terrain::Instance().GetTerrainMaxX() - 1500, transform.GetPosition().y, transform.GetPosition().z);
	else if (transform.GetPosition().x < Terrain::Instance().GetTerrainMinX() + 1500)
		transform.SetPosition(Terrain::Instance().GetTerrainMinX() + 1500, transform.GetPosition().y, transform.GetPosition().z);

	if (transform.GetPosition().z > Terrain::Instance().GetTerrainMaxZ() - 1500)
		transform.SetPosition(transform.GetPosition().x, transform.GetPosition().y, Terrain::Instance().GetTerrainMaxZ() - 1500);
	if (transform.GetPosition().z < Terrain::Instance().GetTerrainMinZ() + 1500)
		transform.SetPosition(transform.GetPosition().x, transform.GetPosition().y, Terrain::Instance().GetTerrainMinZ() + 1500);

	mainCamera->transform.SetPosition(transform.GetPosition());
	gunCam->transform.SetPosition(transform.GetPosition());
	gn->transform.SetPosition(-0.899999, -1.96, 3.68);

}

void Player::UpdateControls()
{

	Transform t = transform;

	static float timer = 0;

	timer += Timer::GetDeltaS();

	if (timer > 0.2)
	{
		//Logger::LogInfo("Delta", Input::GetDeltaMousePosX(), Input::GetDeltaMousePosY());
		timer = 0;
	}

	if (Timer::GetTickCount() == 1)
	{
		Input::Update();
		transform.SetRotation(0, 0, 0);
		return;
	}


	transform.RotateBy(Input::GetDeltaMousePosX() * Timer::GetDeltaS() * GetRotationSpeed(), glm::vec3(0, 1, 0));
	mainCamera->transform.RotateBy(Input::GetDeltaMousePosX() * Timer::GetDeltaS() * GetRotationSpeed(), glm::vec3(0, 1, 0));
	gunCam->transform.RotateBy(Input::GetDeltaMousePosX() * Timer::GetDeltaS() * GetRotationSpeed(), glm::vec3(0, 1, 0));


	t.RotateBy(Input::GetDeltaMousePosY() * Timer::GetDeltaS() * GetRotationSpeed(), transform.GetLocalRight());

	t.UpdateVectors();

	float dot = glm::dot(t.GetLocalFront(), glm::vec3(0, 1, 0));

	if (dot  < 0.8 && dot  > -0.8)
	{
		this->transform.RotateBy(Input::GetDeltaMousePosY() * Timer::GetDeltaS() * GetRotationSpeed(), transform.GetLocalRight());
		mainCamera->transform.RotateBy(Input::GetDeltaMousePosY() * Timer::GetDeltaS() * GetRotationSpeed(), transform.GetLocalRight());
		gunCam->transform.RotateBy(Input::GetDeltaMousePosY() * Timer::GetDeltaS() * GetRotationSpeed(), transform.GetLocalRight());

	}
	else
	{
		transform.SetRotation(0, 0, 0);
		mainCamera->transform.SetRotation(0, 0, 0);
		gunCam->transform.SetRotation(0, 0, 0);
	}



	//Handle forward and backward movement
	if (Input::GetKeyDown(GLFW_KEY_W) == true && Input::GetKeyDown(GLFW_KEY_S) == false)
	{
		this->transform.SetPosition(this->transform.GetPosition() + (GetMovementSpeed() * Timer::GetDeltaS() * this->transform.GetLocalFront()));
		_intendedDir += transform.GetLocalFront();
	}
	else if (Input::GetKeyDown(GLFW_KEY_S) == true && Input::GetKeyDown(GLFW_KEY_W) == false)
	{
		this->transform.SetPosition(this->transform.GetPosition() - (GetMovementSpeed() * Timer::GetDeltaS() * this->transform.GetLocalFront()));
		_intendedDir -= transform.GetLocalFront();

	}

	//Handle side-to-side movement
	if (Input::GetKeyDown(GLFW_KEY_D) == true && Input::GetKeyDown(GLFW_KEY_A) == false)
	{
		this->transform.SetPosition(this->transform.GetPosition() + (GetMovementSpeed() * Timer::GetDeltaS() * this->transform.GetLocalRight()));
		_intendedDir += transform.GetLocalRight();

	}
	else if (Input::GetKeyDown(GLFW_KEY_A) == true && Input::GetKeyDown(GLFW_KEY_D) == false)
	{
		this->transform.SetPosition(this->transform.GetPosition() - (GetMovementSpeed() * Timer::GetDeltaS() * this->transform.GetLocalRight()));
		_intendedDir -= transform.GetLocalRight();

	}

	if (glm::length2(_intendedDir) != 0)
		_intendedDir = glm::normalize(_intendedDir);

	boxCollider->transform.SetPosition(transform.GetGlobalPosition() + _intendedDir * 50.0f);

	if (Input::GetKeyPressed(GLFW_KEY_V))
	{
		_isTopView = !_isTopView;
		transform.SetPosition(0, 2000, 0);

	}


	if (Input::GetKeyDown(GLFW_KEY_T) == true)
		Input::SetCursorMode("normal");
	else if (Input::GetKeyDown(GLFW_KEY_Y) == true)
		Input::SetCursorMode("disabled");

	_movementSpeed = glm::clamp(_movementSpeed, MIN_SPEED, MAX_SPEED);

	counter = 1;


}



void Player::LateUpdate()
{
	_movementSpeed = ORIGINAL_SPEED;
}




void Player::SetMovementSpeed(float speed)
{
	_movementSpeed = speed;
}

void Player::SetRotationSpeed(float speed)
{
	_rotationSpeed = speed;
}

float Player::GetMovementSpeed() const
{
	return _movementSpeed;
}

float Player::GetRotationSpeed() const
{
	return _rotationSpeed;
}