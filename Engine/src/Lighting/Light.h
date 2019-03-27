#pragma once

#include "..\Core\Logger.h"
#include "..\GameObject\Component.h"


class Light : public GameObject
{
public:
	friend class LightManager;

	enum LightType
	{
		POINT,
		DIRECTIONAL
	};
	Light(std::string lightName, LightType type);
	virtual ~Light();


	void GetDiffuseColor(float& r, float& g, float& b);
	void GetSpecularColor(float& r, float& g, float& b);

	glm::vec3& GetDiffuseColor(){ return diffuseColor; }
	glm::vec3& GetSpecularColor(){ return specularColor; }

	void SetDiffuseColor(float r, float g, float b);
	void SetSpecularColor(float r, float g, float b);

	float& GetIntensity() { return intensity; }
	void SetIntensity(float i) { intensity = i; }

	LightType GetType(){ return lightType; }

protected:
	LightType lightType;
	float intensity;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;

};



