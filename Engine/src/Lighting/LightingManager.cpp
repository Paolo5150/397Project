#include "LightingManager.h"
#include "..\Utils\UBOLibrary.h"
#include "..\Utils\AssetLoader.h"
#include "..\Graphics\Layers.h"
#include "..\Graphics\RenderingEngine.h"
#include "..\Utils\Maths.h"
#include "..\Core\CameraOrthogonal.h"


static int POINT_LIGHT_SIZE = 64; //Size in bytes + offsets
static int DIRECTIONAL_LIGHT_SIZE = 128;


LightManager& LightManager::Instance()
{
	static LightManager instance;
	return instance;
}

LightManager::~LightManager()
{
	glDeleteBuffers(1, &pointLightUBO);
	glDeleteBuffers(1, &directionalLightUBO);
	delete shadowCamera;


}

void LightManager::Initialize()
{

	
	shadowCamera = new Camera_Orthogonal(-500, 500, -500, 500, 0.1, 2000.0);
	shadowCamera->RemoveLayerMask(Layers::GUI);
	shadowCamera->RemoveLayerMask(Layers::TERRAIN);
	shadowCamera->RemoveLayerMask(Layers::WATER);
	shadowCamera->SetActive(false);
	fogEnabled = false;
	fogColor = glm::vec3(0.5, 0.5, 0.7);



	//simplifiedMaterial.SetShader(AssetManager::ShaderManager::GetShaderByName("colorOnly"));

	//Directional light UBO
	glGenBuffers(1, &directionalLightUBO);

	int directional_total_size = (MAX_LIGHTS * DIRECTIONAL_LIGHT_SIZE) + 4;

	glBindBuffer(GL_UNIFORM_BUFFER, directionalLightUBO);
	glBufferData(GL_UNIFORM_BUFFER, directional_total_size, NULL, GL_DYNAMIC_DRAW);

	glBindBufferRange(GL_UNIFORM_BUFFER, UBOLibrary::DIRECTIONAL_LIGHTS, directionalLightUBO, 0, directional_total_size);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);


	//Directional light UBO
	glGenBuffers(1, &pointLightUBO);

	int point_total_size = (MAX_LIGHTS * POINT_LIGHT_SIZE) + 4;

	glBindBuffer(GL_UNIFORM_BUFFER, pointLightUBO);
	glBufferData(GL_UNIFORM_BUFFER, point_total_size, NULL, GL_DYNAMIC_DRAW);

	glBindBufferRange(GL_UNIFORM_BUFFER, UBOLibrary::POINT_LIGHTS, pointLightUBO, 0, point_total_size);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);


}

bool LightManager::GetFogEnable()
{
	return fogEnabled;
}


void LightManager::SetFogEnable(bool fe)
{
	fogEnabled = fe;
}

void LightManager::UpdateUBOs()
{

	totalDirLights = alldirectionalLights.size();
	//shadowMaps.clear();

	//Update Directional lights UBO
	auto it = alldirectionalLights.begin();
	glBindBuffer(GL_UNIFORM_BUFFER, directionalLightUBO);
	int i = 0;

	
	//shadowCamera->isActive = 1;
	for (; it != alldirectionalLights.end(); it++)
	{
		if (!(*it)->GetActive())
		{
			totalDirLights--;
			continue;
		}

		/*if ((*it)->GetIsCastingShadow())
		{

			//Create shadow map
			(*it)->shadowMap->Bind();
			glClear(GL_DEPTH_BUFFER_BIT);
			directionalLightShadowCam->transform.position = sceneMainCamera->transform.position - (*it)->direction * 500.0f;
			directionalLightShadowCam->transform.LookAt(directionalLightShadowCam->transform.position + (*it)->direction);
			shadowCamera->UpdateViewMatrix();
			RenderingEngine::Instance().RenderCurrentScene(shadowCamera, &simplifiedMaterial);
			(*it)->shadowMap->Unbind();


			shadowMaps.push_back((*it)->shadowMap);
		}*/
		glBufferSubData(GL_UNIFORM_BUFFER, 0 + i * DIRECTIONAL_LIGHT_SIZE, 64, glm::value_ptr((shadowCamera->projectionMatrix * shadowCamera->viewMatrix)));
		glBufferSubData(GL_UNIFORM_BUFFER, 64 + i * DIRECTIONAL_LIGHT_SIZE, 16, &(*it)->transform.GetPosition());
		glBufferSubData(GL_UNIFORM_BUFFER, 64 + 16 + i * DIRECTIONAL_LIGHT_SIZE, 12, &(*it)->transform.GetLocalFront());
		glBufferSubData(GL_UNIFORM_BUFFER, 64 + 32 + i * DIRECTIONAL_LIGHT_SIZE, 12, &(*it)->GetDiffuseColor());
		glBufferSubData(GL_UNIFORM_BUFFER, 64 + 48 + i * DIRECTIONAL_LIGHT_SIZE, 12, &(*it)->GetSpecularColor());
		glBufferSubData(GL_UNIFORM_BUFFER, 64 + 60 + i * DIRECTIONAL_LIGHT_SIZE, 4, &(*it)->GetIntensity());

		i++;
	}

	//shadowCamera->isActive = 0;
	glBufferSubData(GL_UNIFORM_BUFFER, (MAX_LIGHTS * DIRECTIONAL_LIGHT_SIZE), 4, &totalDirLights);


	//Update point lights UBO
	totalPointLights = allPointLights.size();
	auto it2 = allPointLights.begin();
	glBindBuffer(GL_UNIFORM_BUFFER, pointLightUBO);

	i = 0;
	for (; it2 != allPointLights.end(); it2++)
	{
		if (!(*it2)->GetActive())
		{
			totalPointLights--;
			continue;
		}

		glBufferSubData(GL_UNIFORM_BUFFER, 0 + i * POINT_LIGHT_SIZE, 16, &(*it2)->transform.GetPosition());
		glBufferSubData(GL_UNIFORM_BUFFER, 16 + i * POINT_LIGHT_SIZE, 12,&(*it2)->transform.GetRotation());
		glBufferSubData(GL_UNIFORM_BUFFER, 32 + i * POINT_LIGHT_SIZE, 12,&(*it2)->GetDiffuseColor());
		glBufferSubData(GL_UNIFORM_BUFFER, 48 + i * POINT_LIGHT_SIZE, 12,&(*it2)->GetSpecularColor());
		glBufferSubData(GL_UNIFORM_BUFFER, 60 + i * POINT_LIGHT_SIZE, 4, &(*it2)->GetIntensity());




		i++;
	}

	glBufferSubData(GL_UNIFORM_BUFFER, (MAX_LIGHTS * POINT_LIGHT_SIZE), 4, &totalPointLights);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void LightManager::Update()
{
	UpdateUBOs();

	//Deactivate textures here
	/*for (int i = 0; i < shadowMaps.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + (i + 10));
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glActiveTexture(GL_TEXTURE0);*/
}

// From GL_TEXTURE30 onwards -> SHADOWS
// Between 20 and 30 -> reflection

//Send shadow maps to current shader
void LightManager::UpdateShader(Shader& shader)
{

	shader.Bind(); //This line is kind of vital
	shader.SetVec3("AmbientLight", ambientLight);
	//Load shadow maps
	/*std::string uniformName = "shadowMap[";

	shader.SetInt("shadowMapCount", shadowMaps.size());
	//TODO: improc ve this, cubemap and texture can be bind together, should not be the case
	for (int i = 0; i < shadowMaps.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + (i + 30));

		std::stringstream ss;
		ss << uniformName;
		ss << i;
		ss << ']';
		shader.SetInt(ss.str(), (i + 30));
		shadowMaps[i]->GetDepthTexture()->Bind();
	}*/
}

void LightManager::SubscirbeLight(Light* l)
{
	
	if (l->GetType()== Light::LightType::POINT)
	{
		if (allPointLights.size() < MAX_LIGHTS)
			allPointLights.push_back((PointLight*)l);
	}
	else if (l->GetType() == Light::LightType::DIRECTIONAL)
	{
		if (alldirectionalLights.size() < MAX_LIGHTS)
		{
			alldirectionalLights.push_back((DirectionalLight*)l);
		}
	}
}
void LightManager::RemoveLight(Light *l)
{

	if (l->GetType() == Light::LightType::POINT)
	{
		auto it = allPointLights.begin();

		for (; it != allPointLights.end();)
		{
			if ((*it) == l)
			{
				//Don't delete the light as it is a component and therefore automatically deleted by the entity
				it = allPointLights.erase(it);
			}
			else
				it++;
		}
	}
	else if (l->GetType() == Light::LightType::DIRECTIONAL)
	{
		auto it = alldirectionalLights.begin();

		for (; it != alldirectionalLights.end();)
		{
			if ((*it) == l)
			{
				//Don't delete the light as it is a component and therefore automatically deleted by the entity
				it = alldirectionalLights.erase(it);
			}
			else
				it++;
		}
	}

}

void LightManager::SetAmbientLight(float r, float g, float b)
{
	ambientLight.x = r;
	ambientLight.y = g;
	ambientLight.z = b;

}
