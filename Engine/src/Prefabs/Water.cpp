
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

	waterCamera->SetActive(false);


	int w, h;
	Window::Instance().GetWindowSize(w, h);
	refractionBuffer = Core::Instance().GetGraphicsAPI().CreateFrameBuffer(w, h);
	reflectionBuffer = Core::Instance().GetGraphicsAPI().CreateFrameBuffer(w, h);

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
	meshRenderer = dynamic_cast<MeshRenderer*>(GetChild("QuadMesh")->GetComponentByType("Renderer"));
	meshRenderer->AddPreRenderCallback(std::bind(&Water::OnPreRender, this, std::placeholders::_1, std::placeholders::_2));
	meshRenderer->SetIsCullable(false);
	SetIsStatic(true);
	SetLayer(0);
	SetLayer(Layers::WATER);
	meshRenderer->SetMaterial(*material);
}


Water::~Water()
{
	EventDispatcher::Instance().UnsubscribeCallback<WindowResizeEvent>(waterResizeToken);

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
	//Refraction
	LightManager::Instance().SetClippingPlane(glm::vec4(0, -1, 0, transform.GetPosition().y));
	refractionBuffer->Bind();
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();
	Core::Instance().GetGraphicsAPI().ClearColorBuffer();

	waterCamera->transform = mainCamera->transform;
	waterCamera->Update();
	//Logger::LogInfo("Wat cam", mainCamera->transform.VectorsToString());
	RenderingEngine::Instance().RenderBuffer(waterCamera, MaterialType::NOLIGHT);

	refractionBuffer->Unbind();

	//Reflection
	
	reflectionBuffer->Bind();
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

void Water::OnPreRender(Camera& camera, Shader* currentShader)
{
	//Logger::LogInfo("Water pre render");
	currentShader->SetFloat("timer", timer);

	if (SceneManager::Instance().GetCurrentScene().GetSkyBox() != nullptr && !cubemapLoaded)
	{
		meshRenderer->GetMaterial().LoadCubemap(&SceneManager::Instance().GetCurrentScene().GetSkyBox()->GetCubeMap());
		cubemapLoaded = 1;
	}

}

bool Water::ResizeFrameBuffers(Event* e)
{
	WindowResizeEvent* wc = dynamic_cast<WindowResizeEvent*>(e);

	refractionBuffer->ResizeTexture(wc->width, wc->height);
	reflectionBuffer->ResizeTexture(wc->width, wc->height);
	return 0;
}

