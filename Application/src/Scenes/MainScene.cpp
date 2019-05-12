#include "Components\MeshRenderer.h"
#include "Prefabs\Axis.h"

#include "Core\MainCamera.h"
#include "MainScene.h"
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
#include "Core\Lua.h"
#include "GUI\GUIElements\GUIText.h"
#include "GUI\GUIElements\GUIImage.h"
#include "GUI\GUIElements\GUIProgressBar.h"

#include "Components\Animator.h"

#include "GUI\GUIElements\GUIManager.h"
#include "Components\BoxCollider.h"
#include "Components\SphereCollider.h"
#include "Prefabs\Pumpkin.h"
#include "Prefabs\Crate.h"
#include "Prefabs\Barrel.h"
#include "Prefabs\Cabin.h"
#include "Prefabs\Hive.h"
#include "Prefabs\Player.h"
#include "Prefabs\GranadeLauncher.h"
#include "Utils\PathFinder.h"
#include "Graphics\RenderingEngine.h"
#include "Physics\PhysicsWorld.h"
#include "Prefabs\Player.h"
#include "Components\AIBase.h"

MainCamera* cam;
PointLight* pLight;
DirectionalLight* dirLight;
bool reinit = false;

MainScene::MainScene() : Scene("MainScene")
{

}

void MainScene::LoadAssets() {


	AssetLoader::Instance().LoadModel("Assets\\Models\\Pumpkin\\pumpkin.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Barrel\\barrel.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Crate\\crate.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Gun\\gun.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Hive\\hive.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Mountains\\mountains.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Ship\\ship.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Cabin\\cabin.fbx");
	AssetLoader::Instance().LoadModel("Assets\\Models\\GranadeLauncher\\launcher.fbx", false);


	AssetLoader::Instance().LoadTexture("Assets\\Textures\\manual.png");

	AssetLoader::Instance().LoadModel("Assets\\Models\\Spider\\spider_3.fbx", 0);

	AssetLoader::Instance().LoadTexture("Assets\\Models\\Spider\\textures\\Spinnen_Bein_tex_COLOR_.jpg");
	AssetLoader::Instance().LoadTexture("Assets\\Models\\GranadeLauncher\\launcher.jpg");

	AssetLoader::Instance().LoadTexture("Assets\\Textures\\wood.jpg");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\crate_diffuse.tga");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\crate_normal.tga");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\pumpkinIcon.png");

	AssetLoader::Instance().LoadTexture("Assets\\Textures\\crate_specular.tga");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\shipTexture.png");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\cabin_diffuse.png");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\cabin_normal.png");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\hive_diffuse.jpg");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\hive_normal.jpg");
}
void MainScene::UnloadAssets() {
	AssetLoader::Instance().Unload<Model>();
	AssetLoader::Instance().Unload<Texture2D>();

}
void MainScene::QuitScene() {
	Logger::LogError("Scene asset clean up");

	Scene::QuitScene();

}
void MainScene::Initialize() {

	//Terrain

	Terrain::Instance().Initialize(256);

	skybox = new Skybox(AssetLoader::Instance().GetAsset<CubeMap>("SunSet"));

	Lua::RunLua("Assets\\Scripts\\Level1.lua", false, true);


	//Timer::SetDisplayFPS(true);

	manual = new GUIImage("manualImage", AssetLoader::Instance().GetAsset<Texture2D>("manual"), 10, 10, 80, 80, 1);
	manual->isActive = 0;
	GUIManager::Instance().AddGUIObject(manual);

	// HUD elements
	pumpkinAmmoText = new GUIText("ammoText", "X 50", "invasionFont", 1, 90, 5, 1, 1, 1, 1);
	pumpkinAmmoImage = new GUIImage("pumpkinIcon", AssetLoader::Instance().GetAsset<Texture2D>("pumpkinIcon"), 80, 3, 7, 7, 1);
	GUIManager::Instance().AddGUIObject(pumpkinAmmoText);
	GUIManager::Instance().AddGUIObject(pumpkinAmmoImage);

	healthBar = new GUIProgressBar("", "", 3, 3, 40, 3, 1);
	GUIManager::Instance().AddGUIObject(healthBar);


	//Lights
	LightManager::Instance().SetAmbientLight(0.5f, 0.5f, 0.2f);

	dirLight = new DirectionalLight();
	dirLight->SetDiffuseColor(1, 1, 1);
	dirLight->transform.SetRotation(45, 117, 0);
	dirLight->SetIntensity(0.9f);
	dirLight->SetDiffuseColor(1.0, 1.0, 0.8);


	DirectionalLight* dirLight2 = new DirectionalLight(false);
	dirLight2->SetDiffuseColor(1, 1, 1);
	dirLight2->transform.SetRotation(90, -120, 0);
	dirLight2->SetIntensity(0.5f);

	pLight = new PointLight();
	pLight->SetDiffuseColor(1, 1, 1);
	pLight->transform.Translate(-15, 10, -15);
	pLight->SetIntensity(50.0f);

	PathFinder::Instance().Generate(&Terrain::Instance());
	for (unsigned i = 0; i < PathFinder::Instance().pathNodes.size(); i++)
		AddGameObject(PathFinder::Instance().pathNodes[i]);



	//GameObjects
	for (int i = 0; i < Lua::GetCreatedAssetLength(); i++) //Loop through all the game objects that aren't the player, and add them to the scene
	{
		GameObject* obj = (GameObject*)Lua::GetCreatedAsset(i);
		if (obj->HasComponent("AIBase")) //If the object has an ai component, set its target to the player
		{
			((AIBase*)obj->GetComponent<AIBase>("AIBase"))->SetTarget(((Player*)SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Player").at(0))->transform);
		}
		AddGameObject(obj);
	}

	int x, y, z;
	Terrain::Instance().GetCenter(x, y, z);
	PhysicsWorld::Instance().InitializeQuadtree(x, z, Terrain::Instance().GetTerrainMaxX() - Terrain::Instance().GetTerrainMinX(), Terrain::Instance().GetTerrainMaxZ() - Terrain::Instance().GetTerrainMinZ());

	AddGameObject(dirLight);
	AddGameObject(dirLight2);
	AddGameObject(pLight);
	AddGameObject(&Terrain::Instance());

	Lua::CloseLua();

}

void MainScene::Start()
{
	Scene::Start();


	PathFinder::Instance().Start();

	PhysicsWorld::Instance().FillQuadtree(true);
	PhysicsWorld::Instance().PerformCollisions(true);

	RenderingEngine::godRays = 1;
	Input::SetIsEnabled(1);
}

void MainScene::LogicUpdate()
{
	UpdateUI();
	PhysicsWorld::Instance().Update(Timer::GetDeltaS());

	if (Input::GetKeyPressed(GLFW_KEY_M))
		manual->isActive = !manual->isActive;

	if (Input::GetKeyPressed(GLFW_KEY_ESCAPE) || Input::GetKeyPressed(GLFW_KEY_X))
		SceneManager::Instance().LoadNewScene("ExitScene");

	Scene::LogicUpdate(); //Must be last statement!

	if (Input::GetKeyPressed(GLFW_KEY_R))
		Restart();







	if (Input::GetKeyPressed(GLFW_KEY_1))
	{
		for (auto const& i : GetGameobjectsByName("Hive"))
		{
			Logger::LogInfo("Set state to 0");
			((Hive*)i)->SetState(0);
		}
	}
	else if (Input::GetKeyPressed(GLFW_KEY_2))
	{
		for (auto const& i : GetGameobjectsByName("Hive"))
		{
			Logger::LogInfo("Set state to 1");
			((Hive*)i)->SetState(1);
		}
	}
	else if (Input::GetKeyPressed(GLFW_KEY_3))
	{
		for (auto const& i : GetGameobjectsByName("Hive"))
		{
			Logger::LogInfo("Set state to 2");
			((Hive*)i)->SetState(2);
		}
	}
}

void MainScene::Restart()
{
	Input::SetIsEnabled(0);

	SceneManager::Instance().ReloadCurrent();

}

void MainScene::UpdateUI()
{
	if (player != nullptr)
	{
		std::stringstream ss;
		ss << "x ";
		ss << player->ammoCounter;
		pumpkinAmmoText->_message = ss.str();

		healthBar->percentage = player->healhComponent->GetHealthMaxRatio();

	}
}


