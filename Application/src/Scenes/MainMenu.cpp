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


#include "Core\Input.h"
#include "Event\EventDispatcher.h"
#include "Event\ApplicationEvents.h"


MainMenuScene::MainMenuScene() : Scene("MainMenuScene")
{

}

void MainMenuScene::LoadAssets() {

	AssetLoader::Instance().LoadTexture("Assets\\Textures\\manual.png");


}
void MainMenuScene::UnloadAssets() {

	AssetLoader::Instance().Unload<Texture2D>();
}

void MainMenuScene::QuitScene() {
	Scene::QuitScene();
}

void MainMenuScene::Initialize() {

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

		GUIManager::Instance().RenderNoButtonCallbacks();

		SceneManager::Instance().LoadNewScene("MainScene");



	}, "", 1.5,10, 10, 20, 20, 1, 1, 1, 1));

	loadButton = (new GUIButton("menuLoadButton", "Load Game", [&]{

		if (SaveGameManager::CanLoadGame())
		{
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
			loadFailedText->isActive = 0;

			GUIManager::Instance().RenderNoButtonCallbacks();

			SaveGameManager::loadWhenPossible = true;
			SceneManager::Instance().LoadNewScene("MainScene");
		}
		else
			loadFailedText->isActive = 1;

	}, "", 1.5, 10, 10, 20, 35, 0, 0, 0, 1));

	manualButton = (new GUIButton("menuManualButton", "Game Manual", [&]{
		manualImage->isActive = 1;

	}, "", 1.5, 10, 10, 20, 50, 0, 0, 0, 1));
	
	quitButton = (new GUIButton("menuQuitButton", "Quit Game", [&]{

		SceneManager::Instance().LoadNewScene("ExitScene");

	}, "", 1.5, 10, 10, 20, 65, 1, 0.5, 0.2, 1));

	loadingText = new GUIText("LoadingText", "Loading scene...", "invasionFont", 1.5, 5, 90, 0.9, 0.9, 0.9, 1);
	loadFailedText = new GUIText("LoadFailedText", "Failed to load game or no save file found", "arcadeFont", 1, 10, 90, 0.9, 0.9, 0.9, 1);
	loadingText->isActive = 0;
	loadFailedText->isActive = 0;

	GUIManager::Instance().AddGUIObject(gameTitle);
	GUIManager::Instance().AddGUIObject(menuImage);
	GUIManager::Instance().AddGUIObject(loadingImage);
	GUIManager::Instance().AddGUIObject(loadingText);
	GUIManager::Instance().AddGUIObject(loadFailedText);
	

	GUIManager::Instance().AddGUIObject(startButton);
	GUIManager::Instance().AddGUIObject(loadButton);
	GUIManager::Instance().AddGUIObject(manualButton);
	GUIManager::Instance().AddGUIObject(quitButton);
	GUIManager::Instance().AddGUIObject(gameLogo);
	GUIManager::Instance().AddGUIObject(manualImage);


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

