
#include "Water.h"
#include "..\Graphics\Material.h"
#include "..\Utils\AssetLoader.h"
#include "..\Core\Core.h"
#include "..\Utils\Maths.h"
#include "..\Graphics\RenderingEngine.h"
#include "..\Lighting\LightingManager.h"


Water::Water(Texture2D* normalMap, Texture2D* distortion) : GameObject("Water")
{
	

	Texture2D* waterNormal = normalMap;
	Texture2D* waterDudv = distortion;

	timer = 9;
	waterCamera = new CameraPerspective(60, Window::Instance().GetAspectRatio(), 0.1, 500000);
	waterCamera->RemoveAllMaskLayers();
	waterCamera->AddLayerMask(Layers::DEFAULT);
	waterCamera->AddLayerMask(Layers::TERRAIN);
	waterCamera->SetActive(false);


	int w, h;
	Window::Instance().GetWindowSize(w, h);
	refractionBuffer = Core::Instance().GetGraphicsAPI().CreateFrameBuffer(w/2, h/2);
	reflectionBuffer = Core::Instance().GetGraphicsAPI().CreateFrameBuffer(w/2, h/2);

	material = new Material();
	material->SetShader(AssetLoader::Instance().GetAsset<Shader>("Water"));


	material->Loadtexture(refractionBuffer->GetColorTexture(), TextureUniform::REFRACTION0);
	material->Loadtexture(reflectionBuffer->GetColorTexture(), TextureUniform::REFLECITON0);
	material->Loadtexture(waterNormal, TextureUniform::NORMAL0);
	material->Loadtexture(waterDudv, TextureUniform::SPECIAL0);

	transform.SetRotation(-90, 0, 0);
	material->LoadFloat("shininess", 1000.0f);
	material->SetColor(1.0f, 1.0f, 1.0f);

	material->LoadFloat("UVscale", 10.0f);
	
	GameObject* quadModel = AssetLoader::Instance().GetAsset<Model>("Quad")->CreateGameObject();
	MeshRenderer* mr = dynamic_cast<MeshRenderer*>(quadModel->GetChild("QuadMesh")->GetComponentByType("Renderer"));
	mr->AddPreRenderCallback(std::bind(&Water::OnPreRender, this, std::placeholders::_1, std::placeholders::_2));
	//Logger::LogError("Quadmodel", quadModel->GetName());
	AddChild(quadModel);
	SetLayer(0);
	SetLayer(Layers::WATER);
	ApplyMaterial(*material);
}


Water::~Water()
{
	delete material;
	delete refractionBuffer;
	delete reflectionBuffer;
}

void Water::Update()
{
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
	RenderingEngine::Instance().RenderBufferOverrideColor(waterCamera,glm::vec3(0),MaterialType::COLORONLY);

	reflectionBuffer->Unbind();

	Core::Instance().GetGraphicsAPI().SetClipPlaneActive(false);
	waterCamera->SetActive(0);


}

void Water::OnPreRender(Camera& camera, Shader* currentShader)
{
	//Logger::LogInfo("Water pre render");
	currentShader->SetFloat("timer", timer);


}
/*
bool Water::HandleEvent(Event &ev)
{


	//V2_INFO("Resizing");
	WindowResizeEvent& wc = static_cast<WindowResizeEvent&>(ev);

	//refractionBuffer->ResizeTexture(wc.width, wc.height);
	//reflectionBuffer->ResizeTexture(wc.width, wc.height);

	return 0;
}*/
