#include "MainCamera.h"


MainCamera::MainCamera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) : CameraPerspective(fieldOfView, aspectRatio, nearPlane, farPlane)
{
	_isActive = true;
}

void MainCamera::UpdateControls()
{
	if (GetActive() == true)
	{
		//Handle rotation
		this->transform.RotateBy(Input::GetDeltaMousePosX(), this->transform.GetLocalUp());
		this->transform.RotateBy(Input::GetDeltaMousePosY(), this->transform.GetLocalRight());

		//Handle forward and backward movement
		if (Input::GetKeyDown(GLFW_KEY_W) == true && Input::GetKeyDown(GLFW_KEY_S) == false)
		{
			this->transform.SetPosition(this->transform.GetPosition() + (glm::vec3(2, 2, 2) * this->transform.GetLocalFront()));
		}
		else if (Input::GetKeyDown(GLFW_KEY_S) == true && Input::GetKeyDown(GLFW_KEY_W) == false)
		{
			this->transform.SetPosition(this->transform.GetPosition() - (glm::vec3(2, 2, 2) * this->transform.GetLocalFront()));
		}

		//Handle Side-to-side movement
		if (Input::GetKeyDown(GLFW_KEY_D) == true && Input::GetKeyDown(GLFW_KEY_A) == false)
		{
			this->transform.SetPosition(this->transform.GetPosition() + (glm::vec3(2, 2, 2) * this->transform.GetLocalRight()));
		}
		else if (Input::GetKeyDown(GLFW_KEY_A) == true && Input::GetKeyDown(GLFW_KEY_D) == false)
		{
			this->transform.SetPosition(this->transform.GetPosition() - (glm::vec3(2, 2, 2) * this->transform.GetLocalRight()));
		}
	}
}

void MainCamera::SetActive(bool active)
{
	_isActive = active;
}

bool MainCamera::GetActive() const
{
	return _isActive;
}