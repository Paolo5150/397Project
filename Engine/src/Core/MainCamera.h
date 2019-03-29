#pragma once
#include "CameraPerspective.h"
#include "Input.h"

class MainCamera : public CameraPerspective
{
public:
	MainCamera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);

	void UpdateControls();

	void SetActive(bool active);
	bool GetActive() const;

private:
	bool _isActive;
};

