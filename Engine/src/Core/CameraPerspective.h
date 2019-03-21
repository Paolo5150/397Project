#pragma once
#include "Camera.h"

class CameraPerspective : public Camera
{

public:
	CameraPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	float GetAspectRatio();
	float GetFOV();
	float GetNearPlane();
	float GetFarPlane();

	void OnScreenResize(int w, int h);

private:
	float aspectRatio;
	float FOV;
};