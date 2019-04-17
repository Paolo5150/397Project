#include "MainCamera.h"
#include "Timer.h"

namespace {

	const float MIN_SPEED = 0;
	const float MAX_SPEED = 400;
}

MainCamera::MainCamera() : CameraPerspective(60.0f, Window::Instance().GetAspectRatio(), 0.1f, 10000.0f)
{
	this->SetName("Main Camera");
	_movementSpeed = 20;
	_rotationSpeed = 20;
	_isTopView = false;
}



void MainCamera::Update()
{
	UpdateControls();
	CameraPerspective::Update();
}

void MainCamera::UpdateControls()
{
	//Handle rotation
		if (!_isTopView)
		{
		this->transform.RotateBy(Input::GetDeltaMousePosX() * Timer::GetDeltaS() * GetRotationSpeed(), glm::vec3(0, 1, 0));
		this->transform.RotateBy(Input::GetDeltaMousePosY() * Timer::GetDeltaS() * GetRotationSpeed(), transform.GetLocalRight());
	
			if (glm::dot(transform.GetLocalFront(), glm::vec3(0, -1, 0)) > 0.8 || glm::dot(transform.GetLocalFront(), glm::vec3(0, 1, 0)) > 0.8)
				this->transform.RotateBy(Input::GetDeltaMousePosY() * Timer::GetDeltaS() * GetRotationSpeed(), -transform.GetLocalRight());
		}
		else
		{
			transform.Translate(0, GetMovementSpeed() * Input::GetDeltaMousePosY() * Timer::GetDeltaS(),0);
		}

		//Handle forward and backward movement
		if (Input::GetKeyDown(GLFW_KEY_W) == true && Input::GetKeyDown(GLFW_KEY_S) == false)
		{
			this->transform.SetPosition(this->transform.GetPosition() + (GetMovementSpeed() * Timer::GetDeltaS() * this->transform.GetLocalFront()));
		}
		else if (Input::GetKeyDown(GLFW_KEY_S) == true && Input::GetKeyDown(GLFW_KEY_W) == false)
		{
			this->transform.SetPosition(this->transform.GetPosition() - (GetMovementSpeed() * Timer::GetDeltaS() * this->transform.GetLocalFront()));
		}

		//Handle side-to-side movement
		if (Input::GetKeyDown(GLFW_KEY_D) == true && Input::GetKeyDown(GLFW_KEY_A) == false)
		{
			this->transform.SetPosition(this->transform.GetPosition() + (GetMovementSpeed() * Timer::GetDeltaS() * this->transform.GetLocalRight()));
		}
		else if (Input::GetKeyDown(GLFW_KEY_A) == true && Input::GetKeyDown(GLFW_KEY_D) == false)
		{
			this->transform.SetPosition(this->transform.GetPosition() - (GetMovementSpeed() * Timer::GetDeltaS() * this->transform.GetLocalRight()));
		}
	

	//Handle up and down movement
	/*if (Input::GetKeyDown(GLFW_KEY_R) == true && Input::GetKeyDown(GLFW_KEY_F) == false)
	{
		this->transform.SetPosition(this->transform.GetPosition() + (GetMovementSpeed() * Timer::GetDeltaS() * this->transform.GetLocalUp()));
	}
	else if (Input::GetKeyDown(GLFW_KEY_F) == true && Input::GetKeyDown(GLFW_KEY_R) == false)
	{
		this->transform.SetPosition(this->transform.GetPosition() - (GetMovementSpeed() * Timer::GetDeltaS() * this->transform.GetLocalUp()));
	}*/

	if (Input::GetKeyPressed(GLFW_KEY_V))
	{
		_isTopView = !_isTopView;
		transform.SetPosition(0, 2000, 0);
	}


	if (Input::GetKeyDown(GLFW_KEY_T) == true)
		Input::SetCursorMode("normal");
	else if (Input::GetKeyDown(GLFW_KEY_Y) == true)
		Input::SetCursorMode("disabled");

	if (Input::GetKeyDown(GLFW_KEY_KP_ADD))
		_movementSpeed+=10;
	else if (Input::GetKeyDown(GLFW_KEY_KP_SUBTRACT))
		_movementSpeed-=10;

	_movementSpeed = glm::clamp(_movementSpeed, MIN_SPEED, MAX_SPEED);

	//Logger::LogInfo(transform.ToString());
}

void MainCamera::SetMovementSpeed(float speed)
{
	_movementSpeed = speed;
}

void MainCamera::SetRotationSpeed(float speed)
{
	_rotationSpeed = speed;
}

float MainCamera::GetMovementSpeed() const
{
	return _movementSpeed;
}

float MainCamera::GetRotationSpeed() const
{
	return _rotationSpeed;
}