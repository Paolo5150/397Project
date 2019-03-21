#include "Camera.h"

std::list<Camera*> Camera::allCameras;
std::vector<Camera*> Camera::allCamerasVector;

Camera::Camera(std::string name) : GameObject(name)
{
	cullingMask = 0;
	//cullingMask = Layer::DEFAULT | Layer::GUI;
	//Load all layers
	for (int i = 0; i < 30; i++)
		AddLayerMask(1 << i);
	depth = 0;
	allCameras.push_back(this);
	UpdateOrdererdCameras();
}

void Camera::Update()
{
	GameObject::Update();
	UpdateViewMatrix();

}

void Camera::UpdateViewMatrix()
{
	viewMatrix = glm::mat4();
	viewMatrix = glm::lookAt(transform.GetPosition(), transform.GetPosition() + transform.GetLocalFront(), transform.GetLocalUp());
	
}


/*
bool Camera::HandleEvent(Event& e) {

	WindowResizeEvent& ev = static_cast<WindowResizeEvent&>(e);
	OnScreenResize(ev.width, ev.height);
	return 0;

}*/






void Camera::UpdateOrdererdCameras()
{
	allCamerasVector.clear();

	auto it = allCameras.begin();
	for (; it != allCameras.end(); it++)
		allCamerasVector.push_back(*it);

	std::sort(allCamerasVector.begin(), allCamerasVector.end(), [](Camera* l, Camera* r) {

		return l->GetDepth() > r->GetDepth();
	});


}

Camera::~Camera()
{

	auto it = allCameras.begin();

	for (; it != allCameras.end();)
	{
		if ((*it) == this)
		{
			it = allCameras.erase(it);
		}
		else
			it++;
	}
	Camera::UpdateOrdererdCameras();

}