#include "LightingManager.h"
#include "..\Utils\UBOLibrary.h"
#include "..\Utils\AssetLoader.h"
#include "..\Graphics\Layers.h"
#include "..\Graphics\RenderingEngine.h"
#include "..\Utils\Maths.h"
#include "..\Core\CameraOrthogonal.h"
#include "..\Core\Core.h"


static int POINT_LIGHT_SIZE = 64; //Size in bytes + offsets
static int DIRECTIONAL_LIGHT_SIZE = 128;


LightManager& LightManager::Instance()
{
	static LightManager instance;
	return instance;
}

LightManager::~LightManager()
{

	delete shadowCamera;
	delete direcionalLightsBuffer;
	delete pointLightsBuffer;

}

void LightManager::Initialize()
{	
	shadowCamera = new Camera_Orthogonal(-500, 500, -500, 500, 0.1, 2000.0);
	shadowCamera->RemoveLayerMask(Layers::GUI);
	shadowCamera->RemoveLayerMask(Layers::TERRAIN);
	shadowCamera->RemoveLayerMask(Layers::WATER);
	shadowCamera->RemoveLayerMask(Layers::SKYBOX);

	shadowCamera->SetActive(false);
	fogEnabled = false;
	fogColor = glm::vec3(0.5, 0.5, 0.7);
	sceneMainCamera = nullptr;


	//Directional light UBO
	int directional_total_size = (MAX_LIGHTS * DIRECTIONAL_LIGHT_SIZE) + 4;
	direcionalLightsBuffer = Core::Instance().GetGraphicsAPI().CreateUniformBuffer(directional_total_size, UBOLibrary::DIRECTIONAL_LIGHTS);


	//Directional light UBO
	int point_total_size = (MAX_LIGHTS * POINT_LIGHT_SIZE) + 4;
	pointLightsBuffer = Core::Instance().GetGraphicsAPI().CreateUniformBuffer(point_total_size, UBOLibrary::POINT_LIGHTS);




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
	shadowMaps.clear();

	//Update Directional lights UBO
	auto it = alldirectionalLights.begin();

	direcionalLightsBuffer->Bind();
	int i = 0;

	
	//shadowCamera->isActive = 1;
	for (; it != alldirectionalLights.end(); it++)
	{
		if (!(*it)->GetActive())
		{
			totalDirLights--;
			continue;
		}

		if ((*it)->GetIsCastingShadow())
		{

			//Create shadow map
			(*it)->shadowMap->Bind();
			glClear(GL_DEPTH_BUFFER_BIT);
			shadowCamera->transform.SetPosition(sceneMainCamera->transform.GetPosition() - (*it)->transform.GetLocalFront() * 500.0f);
			shadowCamera->transform.LookAt(shadowCamera->transform.GetPosition() + (*it)->transform.GetLocalFront());
			shadowCamera->UpdateViewMatrix();
			RenderingEngine::Instance().RenderBuffer(shadowCamera, MaterialType::COLORONLY);
			(*it)->shadowMap->Unbind();


			shadowMaps.push_back((*it)->shadowMap);
		}
		direcionalLightsBuffer->AddDataRange(0 + i * DIRECTIONAL_LIGHT_SIZE, 64, glm::value_ptr((shadowCamera->projectionMatrix * shadowCamera->viewMatrix)));
		direcionalLightsBuffer->AddDataRange(64 + i * DIRECTIONAL_LIGHT_SIZE, 16, &(*it)->transform.GetPosition());
		direcionalLightsBuffer->AddDataRange(64 + 16 + i * DIRECTIONAL_LIGHT_SIZE, 12, &(*it)->transform.GetLocalFront());
		direcionalLightsBuffer->AddDataRange(64 + 32 + i * DIRECTIONAL_LIGHT_SIZE, 12, &(*it)->GetDiffuseColor());
		direcionalLightsBuffer->AddDataRange(64 + 48 + i * DIRECTIONAL_LIGHT_SIZE, 12, &(*it)->GetSpecularColor());
		direcionalLightsBuffer->AddDataRange(64 + 60 + i * DIRECTIONAL_LIGHT_SIZE, 4, &(*it)->GetIntensity());

		i++;
	}

	//shadowCamera->isActive = 0;
	direcionalLightsBuffer->AddDataRange( (MAX_LIGHTS * DIRECTIONAL_LIGHT_SIZE), 4, &totalDirLights);


	//Update point lights UBO
	totalPointLights = allPointLights.size();
	auto it2 = allPointLights.begin();
	pointLightsBuffer->Bind();

	i = 0;
	for (; it2 != allPointLights.end(); it2++)
	{
		if (!(*it2)->GetActive())
		{
			totalPointLights--;
			continue;
		}

		pointLightsBuffer->AddDataRange(0 + i * POINT_LIGHT_SIZE, 16, &(*it2)->transform.GetPosition());
		pointLightsBuffer->AddDataRange(16 + i * POINT_LIGHT_SIZE, 12, &(*it2)->transform.GetRotation());
		pointLightsBuffer->AddDataRange(32 + i * POINT_LIGHT_SIZE, 12, &(*it2)->GetDiffuseColor());
		pointLightsBuffer->AddDataRange(48 + i * POINT_LIGHT_SIZE, 12, &(*it2)->GetSpecularColor());
		pointLightsBuffer->AddDataRange(60 + i * POINT_LIGHT_SIZE, 4, &(*it2)->GetIntensity());
		i++;
	}

	pointLightsBuffer->AddDataRange((MAX_LIGHTS * POINT_LIGHT_SIZE), 4, &totalPointLights);
	
}

void LightManager::Update()
{
	if (sceneMainCamera == nullptr)
	{
		sceneMainCamera = Camera::GetCameraByName("Main Camera");
		if (sceneMainCamera == nullptr)
			return;
	}
	UpdateUBOs();

	//Deactivate textures here
	for (int i = 0; i < shadowMaps.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + (i + 10));
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glActiveTexture(GL_TEXTURE0);
}

// From GL_TEXTURE30 onwards -> SHADOWS
// Between 20 and 30 -> reflection

//Send shadow maps to current shader
void LightManager::SendShadowToShader(Shader& shader)
{

	shader.Bind(); //This line is kind of vital
	//Load shadow maps
	std::string uniformName = "shadowMap[";

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
	}
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
