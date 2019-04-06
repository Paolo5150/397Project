#pragma once
#include "CameraPerspective.h"
#include "Input.h"

class MainCamera : public CameraPerspective
{
public:
	MainCamera();


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

