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
#include "Graphics\CubeMap.h"
#include "Graphics\SkyBox.h"
#include "Utils\GameAssetFactory.h"

#include "GUI\GUIElements\GUIText.h"
#include "GUI\GUIElements\GUIManager.h"


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

	skybox = new Skybox(AssetLoader::Instance().GetAsset<CubeMap>("SunSet"));

	Timer::SetDisplayFPS(true);
	
	nanosuit = (GameObject*)GameAssetFactory::Instance().Create("Model", "Nanosuit");

	//Lights
	LightManager::Instance().SetAmbientLight(0.2f, 0.2f, 0.2f);

	dirLight = new DirectionalLight();
	dirLight->SetDiffuseColor(1, 1, 1);
	dirLight->transform.SetRotation(10, 120, 0);
	dirLight->SetIntensity(0.9f);
	dirLight->SetDiffuseColor(1.0, 1.0, 0.8);

	DirectionalLight* dirLight2 = new DirectionalLight(false);
	dirLight2->SetDiffuseColor(1, 1, 1);
	dirLight2->transform.SetRotation(90, -120, 0);
	dirLight2->SetIntensity(0.6f);


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
	nanosuit->transform.Translate(0, -100, -15);


	nanosuit->transform.SetScale(2,2,2);

	float ar = Window::Instance().GetAspectRatio();
	cam = (MainCamera*)GameAssetFactory::Instance().Create("MainCamera");
	cam->transform.SetPosition(0,35, 0);
	cam->transform.SetRotation(30, 180, 0);
	
	//cam->transform.LookAt(nanosuit->transform.GetPosition());
	cam->RemoveLayerMask(Layers::GUI);

	Water* w = (Water*)GameAssetFactory::Instance().Create("Water");
	terrain = new Terrain(256);
	terrain->ApplyHeightMap("Assets\\Textures\\hm1.jpg");
	//terrain->GenerateFaultFormation(64, 0, 40, 0.5f, 1);
	terrain->transform.SetScale(15 ,300, 15);
	terrain->transform.Translate(0, 0, 0);

	AddGameObject(w);

	AddGameObject(dirLight);
	AddGameObject(dirLight2);

	AddGameObject(pLight);
	Axis* a = new Axis();
	a->transform.SetScale(10, 10, 10);
	AddGameObject(a);
	AddGameObject(cam);
	AddGameObject(terrain);
	AddGameObject(nanosuit);

	nanosuit->transform.SetPosition(200, terrain->GetHeightAt(200, 200), 200);

	int x, y, z;
	terrain->GetCenter(x, y, z);
	cam->transform.SetPosition(x, y,z);
	w->transform.SetPosition(x, 100, z);
	w->transform.SetScale(2000, 2000, 1);


}
void TestScene1::LogicUpdate() {
	
	//Logger::LogInfo("Test scene 1 update");

	//quad->transform.Translate(0.1f, 0.0f, 0.0f);
	//Logger::LogInfo("Cam up", cam->transform.VectorsToString());
	//cam->transform.RotateBy(0.5f, cam->transform.GetLocalUp());
	//cam->transform.LookAt(nanosuit->transform.GetPosition());

	nanosuit->transform.RotateBy(0.5f,nanosuit->transform.GetLocalUp());

	//nanosuit->transform.SetPosition(nanosuit->transform.GetPosition() + nanosuit->transform.GetLocalRight() * 0.2f);
	//Logger::LogInfo(cam->transform.ToString());

	pLight->transform.Translate(0.05f, 0, 0);
	float h = terrain->GetHeightAt(cam->transform.GetPosition().x, cam->transform.GetPosition().z);
	//Logger::LogInfo("H ", h);
	cam->transform.SetPosition(cam->transform.GetPosition().x, h + 30, cam->transform.GetPosition().z);

	
	/*static float timer = 0;
	timer += Timer::GetDeltaS();

	if (timer > 5)
		SceneManager::Instance().LoadNewScene("TestScene2");*/


	Scene::LogicUpdate(); //Must be last statement!
}

