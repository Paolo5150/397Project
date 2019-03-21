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



private:
	bool OnScreenResize(Event* e) override;
	float aspectRatio;
	float FOV;
};