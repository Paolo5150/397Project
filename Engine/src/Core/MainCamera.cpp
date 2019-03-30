#include "MainCamera.h"
#include "Timer.h"

MainCamera::MainCamera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) : CameraPerspective(fieldOfView, aspectRatio, nearPlane, farPlane)
{
}

void MainCamera::Update()
{
	UpdateControls();
	CameraPerspective::Update();
}


void MainCamera::UpdateControls()
{
		//Logger::LogInfo("Mose delta", Input::GetDeltaMousePosX());
		//Handle rotation
		this->transform.RotateBy(Input::GetDeltaMousePosX() * Timer::GetDeltaS() * 5.0f, glm::vec3(0,1,0));
		this->transform.RotateBy(Input::GetDeltaMousePosY()* Timer::GetDeltaS() * 5.0f, transform.GetLocalRight());
		
		//Handle forward and backward movement
		if (Input::GetKeyDown(GLFW_KEY_W) == true && Input::GetKeyDown(GLFW_KEY_S) == false)
		{
			this->transform.SetPosition(this->transform.GetPosition() + (2.0f * this->transform.GetLocalFront()));
		}
		else if (Input::GetKeyDown(GLFW_KEY_S) == true && Input::GetKeyDown(GLFW_KEY_W) == false)
		{
			this->transform.SetPosition(this->transform.GetPosition() - (2.0f * this->transform.GetLocalFront()));
		}

		//Handle Side-to-side movement
		if (Input::GetKeyDown(GLFW_KEY_D) == true && Input::GetKeyDown(GLFW_KEY_A) == false)
		{
			this->transform.SetPosition(this->transform.GetPosition() + (2.0f* this->transform.GetLocalRight()));
		}
		else if (Input::GetKeyDown(GLFW_KEY_A) == true && Input::GetKeyDown(GLFW_KEY_D) == false)
		{
			this->transform.SetPosition(this->transform.GetPosition() - (2.0f* this->transform.GetLocalRight()));
		}

}

