#pragma once

#include "DirectionalLight.h"
#include "PointLight.h"
#include "..\GameObject\GameObject.h"
#include "..\Graphics\UniformBuffer.h"
#include <list>
#include <vector>

class Light;

#define MAX_LIGHTS 10

class LightManager
{
public:
	static LightManager& Instance();
	~LightManager();
	void SubscirbeLight(Light* l);
	void RemoveLight(Light *l);
	void Initialize();
	void Update();
	void SendShadowToShader(Shader& shader);
	GameObject* sceneMainCamera;
	glm::vec3 fogColor;
	void SetFogEnable(bool enable);
	bool GetFogEnable();
	void SetAmbientLight(float r, float g, float b);
	glm::vec4& GetClippingPlane(){ return clippingPlane; }
	void SetClippingPlane(glm::vec4 cp){ clippingPlane = cp; }
	int GetShadowMapsCount(){ return shadowMaps.size(); }
	glm::vec3& GetAmbientLight(){ return ambientLight; }

private:
	int totalDirLights;
	int totalPointLights;
	LightManager() {};
	void UpdateUBOs();
	std::list<DirectionalLight*> alldirectionalLights;
	std::list<PointLight*> allPointLights;
	glm::vec3 ambientLight;
	std::vector<FrameBuffer*> shadowMaps;
	bool fogEnabled;
	glm::vec4 clippingPlane;
	GLuint directionalLightUBO;
	GLuint pointLightUBO;

	UniformBuffer* direcionalLightsBuffer;
	UniformBuffer* pointLightsBuffer;


	std::vector<float> pointLightReset;
	std::vector<float> dirLightReset;
	Camera* shadowCamera;

	Material simplifiedMaterial;


};
