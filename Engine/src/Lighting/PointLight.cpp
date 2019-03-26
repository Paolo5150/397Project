#include "PointLight.h"


PointLight::PointLight() : Light("PointLight",POINT)
{
	constant = 1;
	quadratic = 1.8;
	linear = 0.7;
	intensity = 20.0f;
	lightType = POINT;

}
PointLight::~PointLight()
{

}