
#include "Water.h"
#include "..\Graphics\Material.h"
#include "..\Utils\AssetLoader.h"
#include "..\Core\Core.h"
#include "..\Utils\Maths.h"
#include "..\Graphics\RenderingEngine.h"
#include "..\Lighting\LightingManager.h"
#include "..\Scene\SceneManager.h"
#include "..\Core\MainCamera.h"

namespace
{
std::string waterResizeToken;
bool cubemapLoaded = 0;
}


Water::Water(Texture2D* normalMap, Texture2D* distortion) : GameObject("Water")
{
	
	waterResizeToken = EventDispatcher::Instance().SubscribeCallback<WindowResizeEvent>(std::bind(&Water::ResizeFrameBuffers, this, std::placeholders::_1));
	Initialize(normalMap, distortion);	
}

Water::Water() : GameObject("Water")
{
	Initialize(AssetLoader::Instance().GetAsset<Texture2D>("water_normal"), AssetLoader::Instance().GetAsset<Texture2D>("dudv"));
}

void Water::Initialize(Texture2D* normalMap, Texture2D* distortion)
{
	mainCamera = nullptr;

	timer = 0;
	waterCamera = new CameraPerspective(60, Window::Instance().GetAspectRatio(), 0.1, 500000);
	waterCamera->RemoveAllMaskLayers();
	waterCamera->AddLayerMask(Layers::DEFAULT);
	waterCamera->AddLayerMask(Layers::TERRAIN);
	//waterCamera->AddLayerMask(Layers::SKYBOX);


	waterCamera->SetActive(false);


	int w, h;
	Window::Instance().GetWindowSize(w, h);
	refractionBuffer = Core::Instance().GetGraphicsAPI().CreateFrameBuffer(w/4, h/4);
	reflectionBuffer = Core::Instance().GetGraphicsAPI().CreateFrameBuffer(w/4, h/4);

	material = new Material();
	material->SetShader(AssetLoader::Instance().GetAsset<Shader>("Water"));


	material->Loadtexture(normalMap, TextureUniform::NORMAL0);
	material->Loadtexture(distortion, TextureUniform::SPECIAL0);

	material->Loadtexture(refractionBuffer->GetColorTexture(), TextureUniform::REFRACTION0);
	material->Loadtexture(reflectionBuffer->GetColorTexture(), TextureUniform::REFLECITON0);


	transform.SetRotation(-90, 0, 0);
	material->LoadFloat("shininess", 200.0f);
	material->SetColor(0.8, 0.8f, 1.0f);

	material->LoadFloat("UVScale", 3.0f);

	AssetLoader::Instance().GetAsset<Model>("Quad")->PopulateGameObject(this);
	meshRenderer =(GetChild("QuadMesh")->GetComponentByType<MeshRenderer>("Renderer"));
	meshRenderer->AddPreRenderCallback(std::bind(&Water::OnPreRender, this, std::placeholders::_1, std::placeholders::_2));
	meshRenderer->AddPostRenderCallback(std::bind(&Water::OnPostRender, this, std::placeholders::_1, std::placeholders::_2));

	meshRenderer->SetIsCullable(false);
	SetIsStatic(true);
	SetLayer(0);
	SetLayer(Layers::WATER);
	meshRenderer->SetMaterial(*material);
	meshRenderer->GetMaterial().LoadCubemap(&SceneManager::Instance().GetCurrentScene().GetSkyBox()->GetCubeMap());
}


Water::~Water()
{
	EventDispatcher::Instance().UnsubscribeCallback<WindowResizeEvent>(waterResizeToken);

	delete waterCamera;
	delete material;
	delete refractionBuffer;
	delete reflectionBuffer;
}

void Water::Update()
{
	if (mainCamera == nullptr)
	{
		mainCamera = dynamic_cast<MainCamera*>(Camera::GetCameraByName("Main Camera"));
		if (mainCamera == nullptr)
			return;
	}

	GameObject::Update();
	Core::Instance().GetGraphicsAPI().SetClipPlaneActive(true);
	timer += Timer::GetDeltaS();
	

	waterCamera->SetActive(1);
	glm::vec3 color = glm::vec3(0.3,0.3,0.3);
	if (mainCamera->transform.GetPosition().y > transform.GetPosition().y)
	{
	LightManager::Instance().SetClippingPlane(glm::vec4(0, -1, 0, transform.GetPosition().y));
	}
	else
	{
		LightManager::Instance().SetClippingPlane(glm::vec4(0, 1, 0, transform.GetPosition().y));
		color = glm::vec3(0.2,0.2,0.5);

	}
	//Refraction
	refractionBuffer->Bind();
	Core::Instance().GetGraphicsAPI().SetClearColor(0.321, 0.3529, 0.3550);
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();
	Core::Instance().GetGraphicsAPI().ClearColorBuffer();

	waterCamera->transform = mainCamera->transform;
	waterCamera->Update();
	//Logger::LogInfo("Wat cam", mainCamera->transform.VectorsToString());
	RenderingEngine::Instance().RenderBufferOverrideColor(waterCamera,color, MaterialType::NOLIGHT);

	refractionBuffer->Unbind();

	//Reflection
	
	reflectionBuffer->Bind();
	Core::Instance().GetGraphicsAPI().SetClearColor(0.321, 0.3529, 0.3550);
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();
	Core::Instance().GetGraphicsAPI().ClearColorBuffer();

	glm::vec3 ref = glm::reflect(mainCamera->transform.GetLocalFront(), glm::vec3(0, 1, 0));

	float heightDiff = transform.GetPosition().y - mainCamera->transform.GetPosition().y;
	waterCamera->transform.SetPosition(glm::vec3(mainCamera->transform.GetPosition().x, mainCamera->transform.GetPosition().y + heightDiff * 2.0, mainCamera->transform.GetPosition().z));

	waterCamera->transform.LookAt(waterCamera->transform.GetPosition() + ref);
	waterCamera->Update();
	LightManager::Instance().SetClippingPlane(glm::vec4(0, 1, 0, -transform.GetPosition().y));
	RenderingEngine::Instance().RenderBuffer(waterCamera,MaterialType::NOLIGHT);

	reflectionBuffer->Unbind();

	Core::Instance().GetGraphicsAPI().SetClipPlaneActive(false);
	waterCamera->SetActive(0);


}

void Water::OnPostRender(Camera& camera, Shader* currentShader)
{
	glEnable(GL_CULL_FACE);

}

void Water::OnPreRender(Camera& camera, Shader* currentShader)
{
	glDisable(GL_CULL_FACE);

	//Logger::LogInfo("Water pre render");
	currentShader->SetFloat("timer", timer);
	currentShader->SetInt("underwater", mainCamera->transform.GetGlobalPosition().y <  transform.GetPosition().y ? 1 : 0);


	if (SceneManager::Instance().GetCurrentScene().GetSkyBox() != nullptr && !cubemapLoaded)
	{
		meshRenderer->GetMaterial().LoadCubemap(&SceneManager::Instance().GetCurrentScene().GetSkyBox()->GetCubeMap());
		cubemapLoaded = 1;
	}

}

bool Water::ResizeFrameBuffers(Event* e)
{
	WindowResizeEvent* wc = dynamic_cast<WindowResizeEvent*>(e);

	refractionBuffer->ResizeTexture(wc->width/4, wc->height/4);
	reflectionBuffer->ResizeTexture(wc->width/4, wc->height/4);
	return 0;
}

