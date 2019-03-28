
#include "Water.h"
#include "..\Graphics\Material.h"
#include "..\Utils\AssetLoader.h"
#include "..\Core\Core.h"
#include "..\Utils\Maths.h"
#include "..\Graphics\RenderingEngine.h"


float Water::heightPlane;
int Water::heightPlaneActive;


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
	material->LoadFloat("shininess", 500.0f);
	material->SetColor(0.8f, 0.8f, 1.0f);

	material->LoadFloat("UVscale", 10.0f);
	
	GameObject* quadModel = AssetLoader::Instance().GetAsset<Model>("Quad")->CreateGameObject();
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

	timer += Timer::GetDeltaS();
	
	Water::heightPlane = transform.GetPosition().y;
	Water::heightPlaneActive = 1;

	waterCamera->SetActive(1);
	//Refraction
	refractionBuffer->Bind();
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();
	Core::Instance().GetGraphicsAPI().ClearColorBuffer();

	waterCamera->transform = mainCamera->transform;
	waterCamera->Update();
	//Logger::LogInfo("Wat cam", mainCamera->transform.VectorsToString());
	RenderingEngine::Instance().RenderBuffer(waterCamera, MaterialType::COLORONLY);

	refractionBuffer->Unbind();

	//Reflection
	Water::heightPlaneActive = -1;
	reflectionBuffer->Bind();
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();
	Core::Instance().GetGraphicsAPI().ClearColorBuffer();

	glm::vec3 ref = glm::reflect(mainCamera->transform.GetLocalFront(), glm::vec3(0, 1, 0));


	float heightDiff = transform.GetPosition().y - mainCamera->transform.GetPosition().y;
	waterCamera->transform.SetPosition(glm::vec3(mainCamera->transform.GetPosition().x, mainCamera->transform.GetPosition().y + heightDiff * 2.0, mainCamera->transform.GetPosition().z));

	waterCamera->transform.LookAt(waterCamera->transform.GetPosition() + ref);
	waterCamera->Update();

	RenderingEngine::Instance().RenderBufferOverrideColor(waterCamera,glm::vec3(1,1,1),MaterialType::DEFAULT);

	reflectionBuffer->Unbind();
	Water::heightPlaneActive = 0;

	waterCamera->SetActive(0);


}

void Water::OnPreRender(Camera& camera, Shader* currentShader)
{
	//Logger::LogInfo("Water pre render");
	GameObject::OnPreRender(camera, currentShader);

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
