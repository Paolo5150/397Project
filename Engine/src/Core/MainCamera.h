#pragma once
#include "CameraPerspective.h"
#include "Input.h"

class MainCamera : public CameraPerspective
{
public:
	MainCamera(float moveSpeed, float rotationSpeed, float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	MainCamera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);

	void UpdateControls();
	void Update() override;

	void SetMovementSpeed(float speed);
	void SetRotationSpeed(float speed);

	float GetMovementSpeed() const;
	float GetRotationSpeed() const;

private:
	float _movementSpeed;
	float _rotationSpeed;
};

