#include "Components\MeshRenderer.h"
#include "Prefabs\Axis.h"

#include "Core\MainCamera.h"
#include "TestScene1.h"
#include "Core/Logger.h"
#include "Scene/SceneManager.h"

#include "Core\Window.h"
#include "Utils\AssetLoader.h"
#include "Lighting\LightingManager.h"
#include "Prefabs\Water.h"
#include "Prefabs\Terrain.h"

#include "GLFW\glfw3.h"


MainCamera* cam;
GameObject* nanosuit;
PointLight* pLight;
DirectionalLight* dirLight;
Terrain* terrain;


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
	LightManager::Instance().SetAmbientLight(0.0f, 0.0f, 0.0f);

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


	// Uncomment this to force a wood material!
	Material mat;
	mat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStatic"));
	mat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("wood"));
	mat.LoadFloat("shininess", 1000.0f);

	nanosuit->ApplyMaterial(mat);
	nanosuit->ApplyColor(1, 1, 1);
	nanosuit->transform.Translate(0, 10, -15);
	nanosuit->transform.SetRotation(45, 0, 0);

	nanosuit->transform.SetScale(2,2,2);


	float ar = Window::Instance().GetAspectRatio();
	cam = new MainCamera(20.0f, 20.0f, 60.0f, Window::Instance().GetAspectRatio(), 0.1f, 1000.0f);
	cam->transform.SetPosition(0,35, 30);
	cam->transform.SetRotation(30, 180, 0);

	//cam->transform.LookAt(nanosuit->transform.GetPosition());
	cam->RemoveLayerMask(Layers::GUI);

	Water* w = new Water();
	w->transform.SetPosition(0, 0, 0);
	w->transform.SetScale(30, 30, 1);
	w->mainCamera = dynamic_cast<MainCamera*>(cam);

	terrain = new Terrain(225);
	terrain->ApplyHeightMap("Assets\\Textures\\hm2.jpg",80);
	//terrain->GenerateFaultFormation(64, 0, 40, 0.5f, 1);
	terrain->transform.SetScale(5 ,1, 5);

	w->PrintHierarchy();
	AddGameObject(w);


	AddGameObject(dirLight);
	//AddGameObject(pLight);
	Axis* a = new Axis();
	a->transform.SetScale(10, 10, 10);
	AddGameObject(a);
	AddGameObject(cam);
	AddGameObject(terrain);
	AddGameObject(nanosuit);




}
void TestScene1::LogicUpdate() {
	
	//Logger::LogInfo("Test scene 1 update");

	//quad->transform.Translate(0.1f, 0.0f, 0.0f);
	//Logger::LogInfo("Cam up", cam->transform.VectorsToString());
	//cam->transform.RotateBy(0.5f, cam->transform.GetLocalUp());
	//cam->transform.LookAt(nanosuit->transform.GetPosition());

	//nanosuit->transform.RotateBy(0.5f,nanosuit->transform.GetLocalUp());

	//nanosuit->transform.SetPosition(nanosuit->transform.GetPosition() + nanosuit->transform.GetLocalRight() * 0.2f);
	//Logger::LogInfo(cam->transform.ToString());

	pLight->transform.Translate(0.05f, 0, 0);

	/*static float timer = 0;
	timer += Timer::GetDeltaS();

	if (timer > 3)
		dirLight->SetActive(false);*/


	Scene::LogicUpdate(); //Must be last statement!
}

