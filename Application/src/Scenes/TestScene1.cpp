#include "Components\MeshRenderer.h"
#include "Prefabs\Axis.h"

#include "Core\CameraPerspective.h"
#include "TestScene1.h"
#include "Core/Logger.h"
#include "Scene/SceneManager.h"
#include "Prefabs\Quad.h"
#include "Core\Window.h"
#include "Utils\AssetLoader.h"
#include "Lighting\LightingManager.h"
#include "Prefabs\Water.h"


GameObject* nanosuit;
PointLight* pLight;
DirectionalLight* dirLight;



TestScene1::TestScene1() : Scene("TestScene1")
{

}

void TestScene1::LoadAssets() {

	AssetLoader::Instance().LoadModel("Assets\\Models\\Nanosuit\\nanosuit.obj");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\wood.jpg");
	
}
void TestScene1::UnloadAssets() {
	AssetLoader::Instance().Unload<Model>();
	AssetLoader::Instance().Unload<Texture2D>();

}
void TestScene1::ExitScene() {
	Logger::LogError("Scene asset clean up");

	Scene::ExitScene();

}
void TestScene1::Initialize() {

	//Timer::SetDisplayFPS(true);
	
	nanosuit = AssetLoader::Instance().GetAsset<Model>("Nanosuit")->CreateGameObject();

	//Lights
	LightManager::Instance().SetAmbientLight(0.2f, 0.2f, 0.2f);

	dirLight = new DirectionalLight();
	dirLight->SetDiffuseColor(1, 1, 1);
	dirLight->transform.SetRotation(45, 180, 0);
	dirLight->SetIsStatic(true);



	dirLight->SetIntensity(2.0f);
	dirLight->Update();

	pLight = new PointLight();
	pLight->SetDiffuseColor(1, 1, 1);
	pLight->transform.Translate(-15, 10, -15);
	pLight->SetIntensity(10.0f);
	pLight->SetActive(false);

	// Uncomment this to force a wood material!
	Material mat;
	mat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStatic"));
	mat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("wood"));
	mat.LoadFloat("shininess", 1000.0f);

	nanosuit->ApplyMaterial(mat);
	nanosuit->ApplyColor(1, 1, 1);
	nanosuit->transform.Translate(0, 0, -20);
	//nanosuit->transform.SetRotation(70, 180, 0);
	//nanosuit->transform.RotateBy(70, 1, 0, 0);
	nanosuit->transform.SetScale(2,2,2);


	float ar = Window::Instance().GetAspectRatio();
	cam = new CameraPerspective(60.0f, Window::Instance().GetAspectRatio(), 0.1f, 1000.0f);
	cam->transform.SetPosition(0,35, 30);
	cam->transform.SetRotation(30, 180, 0);

	//cam->transform.LookAt(nanosuit->transform.GetPosition());
	cam->RemoveLayerMask(Layers::GUI);

	Water* w = new Water();
	w->transform.SetPosition(0, 0, -20);
	w->transform.SetScale(30, 30, 1);
	w->mainCamera = dynamic_cast<CameraPerspective*>(cam);

	w->PrintHierarchy();
	AddGameObject(w);

	AddGameObject(dirLight);
	//AddGameObject(pLight);
	
	AddGameObject(cam);
	
	AddGameObject(nanosuit);




}
void TestScene1::LogicUpdate() {

	//Logger::LogInfo("Test scene 1 update");

	//quad->transform.Translate(0.1f, 0.0f, 0.0f);

	
	nanosuit->transform.RotateBy(0.5f, 0, 1, 0);
	//nanosuit->transform.SetPosition(nanosuit->transform.GetPosition() + nanosuit->transform.GetLocalRight() * 0.5f);
	//Logger::LogWarning(nanosuit->transform.VectorsToString());

	//pLight->transform.Translate(0.05f, 0, 0);

	/*static float timer = 0;
	timer += Timer::GetDeltaS();

	if (timer > 3)
		dirLight->SetActive(false);*/


	Scene::LogicUpdate(); //Must be last statement!
}

