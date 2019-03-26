#pragma once
#include "Light.h"


class PointLight : public Light
{
public:
	friend class LightManager;

	PointLight();
	~PointLight();

	float constant;
	float quadratic;
	float linear;
};
