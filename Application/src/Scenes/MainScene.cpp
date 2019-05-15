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
#include "GUI\GUIElements\GUIButton.h"


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
#include "Prefabs\Spider.h"
#include "Components\AIBase.h"

MainCamera* cam;
bool reinit = false;

MainScene::MainScene() : Scene("MainScene")
{

}

void MainScene::LoadAssets() {


	AssetLoader::Instance().LoadModel("Assets\\Models\\Pumpkin\\pumpkin.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\PumpkinBunch\\pumpkinbunch.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Barrel\\barrel.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Crate\\crate.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Hive\\hive.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Ship\\ship.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Cabin\\cabin.fbx");
	AssetLoader::Instance().LoadModel("Assets\\Models\\GranadeLauncher\\launcher.fbx", false);

	AssetLoader::Instance().LoadTexture("Assets\\Textures\\manual.png");

	AssetLoader::Instance().LoadModel("Assets\\Models\\Spider\\spider_3.fbx", 0);

	AssetLoader::Instance().LoadTexture("Assets\\Models\\Spider\\textures\\Spinnen_Bein_tex_COLOR_.jpg");
	AssetLoader::Instance().LoadTexture("Assets\\Models\\GranadeLauncher\\launcher.jpg");

	AssetLoader::Instance().LoadTexture("Assets\\Textures\\crate_diffuse.tga");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\crate_normal.tga");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\pumpkinIcon.png");

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
	//Terrain::Instance().Initialize(512);

	skybox = new Skybox(AssetLoader::Instance().GetAsset<CubeMap>("SunSet"));

	Lua::RunLua("Assets\\Scripts\\Level1.lua", false, true);


	//Timer::SetDisplayFPS(true);

	manual = new GUIImage("manualImage", AssetLoader::Instance().GetAsset<Texture2D>("manual"), 10, 10, 80, 80, 1);
	manual->isActive = 0;
	GUIManager::Instance().AddGUIObject(manual);

	// HUD elements
	pumpkinAmmoText = new GUIText("ammoText", "X 50", "invasionFont", 1, 90, 5, 1, 1, 1, 1);
	pumpkinAmmoImage = new GUIImage("pumpkinIcon", AssetLoader::Instance().GetAsset<Texture2D>("pumpkinIcon"), 80, 3, 7, 7, 1);
	endGameText = new GUIText("EndGameText", "", "invasionFont", 2, 40, 10, 1, 1, 1, 1);
	endGameText->isActive = 0;

	GUIManager::Instance().AddGUIObject(pumpkinAmmoText);
	GUIManager::Instance().AddGUIObject(pumpkinAmmoImage);
	GUIManager::Instance().AddGUIObject(endGameText);


	healthBar = new GUIProgressBar("", "", 3, 3, 40, 3, 1);
	GUIManager::Instance().AddGUIObject(healthBar);


	//Lights
	LightManager::Instance().SetAmbientLight(0.5f, 0.5f, 0.2f);

	DirectionalLight* dirLight = new DirectionalLight();
	dirLight->SetDiffuseColor(1, 1, 1);
	dirLight->transform.SetRotation(45, 117, 0);
	dirLight->SetIntensity(0.9f);
	dirLight->SetDiffuseColor(1.0, 1.0, 0.8);


	DirectionalLight* dirLight2 = new DirectionalLight(false);
	dirLight2->SetDiffuseColor(1, 1, 1);
	dirLight2->transform.SetRotation(90, -120, 0);
	dirLight2->SetIntensity(0.5f);

	PathFinder::Instance().Generate(&Terrain::Instance());
	/*for (unsigned i = 0; i < PathFinder::Instance().pathNodes.size(); i++)
		AddGameObject(PathFinder::Instance().pathNodes[i]);*/

	//GameObjects
	for (int i = 0; i < Lua::GetCreatedAssetLength(); i++) //Loop through all the game objects and add them to the scene
	{
		GameObject* obj = (GameObject*)Lua::GetCreatedAsset(i);
		if (obj->HasComponent("AIBase")) //If the object has an ai component, set its target to the player (Warning: Player must be created before any AI)
		{
			((AIBase*)obj->GetComponent<AIBase>("AIBase"))->SetTarget(((Player*)SceneManager::Instance().GetCurrentScene().GetGameobjectsByName("Player").at(0))->transform);
		}
		AddGameObject(obj);
	}

	player = ((Player*)GetGameobjectsByName("Player").at(0));

	int x, y, z;
	Terrain::Instance().GetCenter(x, y, z);
	PhysicsWorld::Instance().InitializeQuadtree(x, z, Terrain::Instance().GetTerrainMaxX() - Terrain::Instance().GetTerrainMinX(), Terrain::Instance().GetTerrainMaxZ() - Terrain::Instance().GetTerrainMinZ());

	AddGameObject(dirLight);
	AddGameObject(dirLight2);
	AddGameObject(&Terrain::Instance());

	Lua::CloseLua();

	currentSceneState = PLAYING;

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
	if (currentSceneState == PLAYING)
	{

		if (player->healhComponent->IsDead())
		{
			currentSceneState = GAMEOVER;
		}

		UpdateUI();

		if (Input::GetKeyPressed(GLFW_KEY_M))
			manual->isActive = !manual->isActive;

		Scene::LogicUpdate(); //Must be last statement!

		if (Input::GetKeyPressed(GLFW_KEY_R))
			Restart();


		if (Input::GetKeyPressed(GLFW_KEY_ESCAPE) || Input::GetKeyPressed(GLFW_KEY_X))
			currentSceneState = PAUSE;
	}
	else if (currentSceneState == PAUSE)
	{
		

		if (Input::GetKeyPressed(GLFW_KEY_ESCAPE) || Input::GetKeyPressed(GLFW_KEY_X))
		{
			Logger::LogInfo("Resume");
			currentSceneState = PLAYING;
		}
			
	}
	else if (currentSceneState == WIN)
	{
		endGameText->_message = "YOU WIN!";
		DisplayMenu();
	}
	else if (currentSceneState == GAMEOVER)
	{
	
		endGameText->_message = "YOU'RE DEAD!";
		DisplayMenu();

	}


	PhysicsWorld::Instance().Update(Timer::GetDeltaS());


}

void MainScene::DisplayMenu()
{
	pumpkinAmmoImage->isActive = false;
	healthBar->isActive = false;
	pumpkinAmmoText->isActive = 0;
	endGameText->isActive = 1;
	GUIManager::Instance().SetBackgroundColor(0, 0, 0, 1);
	Input::SetCursorMode("normal");
	GUIButton* restartButton = (new GUIButton("RestartButton", "Restart", [&]{

		Input::SetCursorMode("disabled");
		GUIManager::Instance().SetBackgroundColor(0, 0, 0, 0);
		GUIManager::Instance().RenderNoButtonCallbacks();
		Restart();

	}, "", 1.5, 10, 10, 45, 45, 1, 1, 1, 1));

	GUIButton* quitToMenu = (new GUIButton("QuitToMenuButton", "Menu", [&]{
			
		GUIManager::Instance().SetBackgroundColor(0, 0, 0, 0);
		GUIManager::Instance().RenderNoButtonCallbacks();
		SceneManager::Instance().LoadNewScene("MainMenuScene");

	}, "", 1.5, 10, 10, 45, 60, 1, 1, 1, 1));

	GUIButton* quit = (new GUIButton("QuitButton", "Quit", [&]{

		GUIManager::Instance().SetBackgroundColor(0, 0, 0, 0);
		GUIManager::Instance().RenderNoButtonCallbacks();
		SceneManager::Instance().LoadNewScene("ExitScene");

	}, "", 1.5, 10, 10, 45, 75, 1, 1, 1, 1));

	GUIManager::Instance().AddGUIObject(restartButton);
	GUIManager::Instance().AddGUIObject(quitToMenu);
	GUIManager::Instance().AddGUIObject(quit);



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


