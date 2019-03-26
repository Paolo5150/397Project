#pragma once

#include "DirectionalLight.h"
#include "PointLight.h"
#include "..\GameObject\GameObject.h"
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
	void UpdateShader(Shader& shader);
	GameObject* sceneMainCamera;
	glm::vec3 fogColor;
	void SetFogEnable(bool enable);
	bool GetFogEnable();
	void SetAmbientLight(float r, float g, float b);





private:
	int totalDirLights;
	int totalPointLights;
	LightManager() {};
	void UpdateUBOs();
	std::list<DirectionalLight*> alldirectionalLights;
	std::list<PointLight*> allPointLights;
	glm::vec3 ambientLight;
	//std::vector<FrameBuffer*> shadowMaps;
	bool fogEnabled;

	GLuint directionalLightUBO;
	GLuint pointLightUBO;

	std::vector<float> pointLightReset;
	std::vector<float> dirLightReset;

	GameObject* directionalLightShadowCam;
	Camera* shadowCamera;

	Material simplifiedMaterial;


};
