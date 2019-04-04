#include "MainCamera.h"
#include "Timer.h"

MainCamera::MainCamera(float moveSpeed, float rotationSpeed, float fieldOfView, float aspectRatio, float nearPlane, float farPlane) : CameraPerspective(fieldOfView, aspectRatio, nearPlane, farPlane)
{
	_movementSpeed = moveSpeed;
	_rotationSpeed = rotationSpeed;
}

MainCamera::MainCamera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) : CameraPerspective(fieldOfView, aspectRatio, nearPlane, farPlane)
{
	_movementSpeed = 20.0f;
	_rotationSpeed = 20.0f;
}

void MainCamera::Update()
{
	UpdateControls();
	CameraPerspective::Update();
}

void MainCamera::UpdateControls()
{
	//Handle rotation
	this->transform.RotateBy(Input::GetDeltaMousePosX() * Timer::GetDeltaS() * GetRotationSpeed(), glm::vec3(0, 1, 0));
	this->transform.RotateBy(Input::GetDeltaMousePosY() * Timer::GetDeltaS() * GetRotationSpeed(), transform.GetLocalRight());

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
	if (Input::GetKeyDown(GLFW_KEY_R) == true && Input::GetKeyDown(GLFW_KEY_F) == false)
	{
		this->transform.SetPosition(this->transform.GetPosition() + (GetMovementSpeed() * Timer::GetDeltaS() * this->transform.GetLocalUp()));
	}
	else if (Input::GetKeyDown(GLFW_KEY_F) == true && Input::GetKeyDown(GLFW_KEY_R) == false)
	{
		this->transform.SetPosition(this->transform.GetPosition() - (GetMovementSpeed() * Timer::GetDeltaS() * this->transform.GetLocalUp()));
	}

	if (Input::GetKeyDown(GLFW_KEY_T) == true)
		Input::SetCursorMode("normal");
	else if (Input::GetKeyDown(GLFW_KEY_Y) == true)
		Input::SetCursorMode("disabled");

	if (Input::GetKeyDown(GLFW_KEY_KP_ADD))
		_movementSpeed++;
	else if (Input::GetKeyDown(GLFW_KEY_KP_SUBTRACT))
		_movementSpeed--;


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