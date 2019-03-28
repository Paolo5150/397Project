
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


	material->Loadtexture(refractionBuffer->GetColorTexture(), TextureUniform::REFRACTION0);
	material->Loadtexture(reflectionBuffer->GetColorTexture(), TextureUniform::REFLECITON0);
	material->Loadtexture(waterNormal, TextureUniform::NORMAL0);
	material->Loadtexture(waterDudv, TextureUniform::SPECIAL0);

	transform.SetRotation(-90, 0, 0);
	material->LoadFloat("shininess", 100.0f);
	material->LoadFloat("UVscale", 4.0f);
	
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
	Water::heightPlane = transform.GetPosition().y;
	Water::heightPlaneActive = 1;

	//waterCamera->SetActive(1);
	//Refraction
	/*refractionBuffer->Bind();
	Core::Instance().GetGraphicsAPI().ClearDepthBuffer();
	Core::Instance().GetGraphicsAPI().ClearColorBuffer();

	waterCamera->transform = mainCamera->transform;
	waterCamera->Update();
	RenderingEngine::Instance().RenderBuffer(waterCamera, MaterialType::COLORONLY);

	refractionBuffer->Unbind();*/

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
	Logger::LogInfo("START WATER REND");
	RenderingEngine::Instance().RenderBuffer();
	Logger::LogInfo("END WATER REND");


	reflectionBuffer->Unbind();
	Water::heightPlaneActive = 0;

	waterCamera->SetActive(0);


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
