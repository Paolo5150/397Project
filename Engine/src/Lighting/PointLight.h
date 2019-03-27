#pragma once
#include "Light.h"


class PointLight : public Light
{
public:
	friend class LightManager;

	PointLight();
	~PointLight();

	void Update() override;


private:
};
