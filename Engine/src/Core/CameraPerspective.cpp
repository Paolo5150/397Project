#include "CameraPerspective.h"


CameraPerspective::CameraPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) : Camera("Camera_Perspective")
{
	camerType = PERSPECTIVE;

	this->aspectRatio = aspectRatio;
	this->FOV = fieldOfView;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;

	projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);

}

void CameraPerspective::OnScreenResize(int w, int h)
{
	this->aspectRatio = w / (float)h;
	projectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, nearPlane, farPlane);

}


float CameraPerspective::GetAspectRatio() { return aspectRatio; }
float CameraPerspective::GetFOV() { return FOV; }
float CameraPerspective::GetNearPlane() { return nearPlane; }
float CameraPerspective::GetFarPlane() { return farPlane; }