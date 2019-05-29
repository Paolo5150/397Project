#include "Components\MeshRenderer.h"
#include "Core\CameraPerspective.h"
#include "MainMenu.h"
#include "Core/Logger.h"
#include "Scene/SceneManager.h"

#include "Core\Window.h"
#include "Utils\AssetLoader.h"
#include "GUI\GUIElements\GUIManager.h"
#include "GUI\GUIElements\GUIButton.h"
#include "GUI\GUIElements\GUIProgressBar.h"
#include "Prefabs\Water.h"
#include "Prefabs\Terrain.h"
#include "Core\MainCamera.h"
#include "Lighting\DirectionalLight.h"

#include "Core\Input.h"
#include "Event\EventDispatcher.h"
#include "Event\ApplicationEvents.h"

MainCamera* camera;
MainMenuScene::MainMenuScene() : Scene("MainMenuScene")
{

}

void MainMenuScene::LoadAssets() {

	AssetLoader::Instance().LoadTexture("Assets\\Textures\\manual.jpg");


}
void MainMenuScene::UnloadAssets() {

	AssetLoader::Instance().Unload<Texture2D>();
}

void MainMenuScene::QuitScene() {
	Scene::QuitScene();
}

void MainMenuScene::Initialize() {

	Terrain::Instance().Initialize(256);
	//Terrain::Instance().Initialize(512);

	skybox = new Skybox(AssetLoader::Instance().GetAsset<CubeMap>("SunSet"));

	int wx, wy;
	Window::Instance().GetWindowSize(wx, wy);
	loadingImage = new GUIImage("Logo", AssetLoader::Instance().GetAsset<Texture2D>("logo"),5,5,90,90,1);
	manualImage = new GUIImage("IntroManual", AssetLoader::Instance().GetAsset<Texture2D>("manual"), 5, 5, 90, 90, 1);
	manualImage->isActive = 0;

	loadingImage->isActive = 0;


	Input::SetCursorMode("normal");
	
	gameTitle = (new GUIText("gameTitle", "Pumpkin Sacrifice", "invasionFont", 2, 28, 5, 1, 1, 1, 1));

	AssetLoader::Instance().LoadTexture("Assets\\Textures\\pumpkinIcon.png");
	gameLogo = (new GUIImage("gameLogo", AssetLoader::Instance().GetAsset<Texture2D>("pumpkinIcon"), 40, 35, 40, 40, 1));

	AssetLoader::Instance().LoadTexture("Assets\\Textures\\Sunset.png");
	menuImage = (new GUIImage("menuImage", AssetLoader::Instance().GetAsset<Texture2D>("Sunset"), 0, 0, 100, 100, 1));
	
	startButton = (new GUIButton("tet", "New Game", [&]{

		Input::SetCursorMode("disabled");
		//GUIManager::Instance().SetBackgroundColor(0, 0, 0, 0);
		//loadingImage->isActive = 1;
		startButton->isActive = 0;
		gameLogo->isActive = 0;
		gameTitle->isActive = 0;
		loadButton->isActive = 0;
		manualButton->isActive = 0;
		quitButton->isActive = 0;
		loadingText->isActive = 1;
		loadingImage->isActive = 1;
		GUIManager::Instance().RenderNoButtonCallbacks();

		SceneManager::Instance().LoadNewScene("MainScene");



	}, "", 1.5,10, 10, 20, 20, 1, 1, 1, 1));

	loadButton = (new GUIButton("menuLoadButton", "Load Game", [&]{

		//Load Game Here
	}, "", 1.5, 10, 10, 20, 35, 0, 0, 0, 1));

	manualButton = (new GUIButton("menuManualButton", "Game Manual", [&]{
		manualImage->isActive = 1;

	}, "", 1.5, 10, 10, 20, 50, 0, 0, 0, 1));
	
	quitButton = (new GUIButton("menuQuitButton", "Quit Game", [&]{

		SceneManager::Instance().LoadNewScene("ExitScene");

	}, "", 1.5, 10, 10, 20, 65, 1, 0.5, 0.2, 1));

	loadingText = new GUIText("LoadingText", "Loading scene...", "invasionFont", 1.5, 5, 90, 0.9, 0.9, 0.9, 1);
	loadingText->isActive = 0;

	GUIManager::Instance().AddGUIObject(gameTitle);
	//GUIManager::Instance().AddGUIObject(menuImage);
	GUIManager::Instance().AddGUIObject(loadingImage);
	GUIManager::Instance().AddGUIObject(loadingText);
	

	GUIManager::Instance().AddGUIObject(startButton);
	GUIManager::Instance().AddGUIObject(loadButton);
	GUIManager::Instance().AddGUIObject(manualButton);
	GUIManager::Instance().AddGUIObject(quitButton);
	GUIManager::Instance().AddGUIObject(gameLogo);
	GUIManager::Instance().AddGUIObject(manualImage);

	camera = new MainCamera();
	camera->transform.SetRotation(0, 300, 0);


	int x, y, z;
	Terrain::Instance().GetCenter(x, y, z);
	camera->transform.SetPosition(x+500, 2000, z+500);

	DirectionalLight* dirLight = new DirectionalLight();
	dirLight->SetDiffuseColor(1, 1, 1);
	dirLight->transform.SetRotation(70, 117, 0);
	dirLight->SetIntensity(0.9f);
	dirLight->SetDiffuseColor(1.0, 1.0, 0.8);
	
	Water* water = new Water();
	water->transform.SetPosition(x, y+1000, z);
	water->transform.SetScale(5000, 5000, 5000);

	AddGameObject(&Terrain::Instance());
	AddGameObject(water);
	AddGameObject(camera);




}
void MainMenuScene::LogicUpdate() {
	//Logger::LogInfo("Updating scene", name);


	if (manualImage->isActive)	
	{
		if (Input::GetMouseDown(0) || Input::GetKeyPressed(GLFW_KEY_ESCAPE) || Input::GetKeyPressed(GLFW_KEY_X))
			manualImage->isActive = 0;
	}
	else
	{
		if (Input::GetKeyPressed(GLFW_KEY_ESCAPE) || Input::GetKeyPressed(GLFW_KEY_X))
			SceneManager::Instance().LoadNewScene("ExitScene");
	}

	Scene::LogicUpdate();
}

