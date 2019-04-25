#include "Components\MeshRenderer.h"
#include "Core\CameraPerspective.h"
#include "MainMenu.h"
#include "Core/Logger.h"
#include "Scene/SceneManager.h"

#include "Core\Window.h"
#include "Utils\AssetLoader.h"
#include "GUI\GUIElements\GUIManager.h"
#include "GUI\GUIElements\GUIButton.h"

#include "Core\Input.h"
#include "Event\EventDispatcher.h"
#include "Event\ApplicationEvents.h"


MainMenuScene::MainMenuScene() : Scene("MainMenuScene")
{

}

void MainMenuScene::LoadAssets() {



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
	loadingImage = new GUIImage("Logo", AssetLoader::Instance().GetAsset<Texture2D>("logo"),
		0 + 50, 0 + 50,
		wx - 100, wy - 50);

	loadingImage->isActive = 0;


	Input::SetCursorMode("normal");
	startButton = (new GUIButton("tet", "Start", [&]{

		Input::SetCursorMode("disabled");
		GUIManager::Instance().SetBackgroundColor(0, 0, 0, 0);
		loadingImage->isActive = 1;
		startButton->isActive = 0;
		loadingText->isActive = 1;

		GUIManager::Instance().RenderNoButtonCallbacks();

		SceneManager::Instance().LoadNewScene("MainScene");



	}, "", 10, 10, 45, 45, 1, 1, 1, 1));

	loadingText = new GUIText("LoadingText", "Loading scene...", "invasionFont", 20, wy - 50, 0.2f, 0.2f, 0.2f);
	loadingText->isActive = 0;
	GUIManager::Instance().AddGUIObject(startButton);
	GUIManager::Instance().AddGUIObject(loadingImage);
	GUIManager::Instance().AddGUIObject(loadingText);

}
void MainMenuScene::LogicUpdate() {
	//Logger::LogInfo("Updating scene", name);

	if (Input::GetKeyPressed(GLFW_KEY_ESCAPE) || Input::GetKeyPressed(GLFW_KEY_X))
		SceneManager::Instance().LoadNewScene("ExitScene");


	if (Input::GetKeyPressed(GLFW_KEY_ENTER))
	{
		GUIManager::Instance().SetBackgroundColor(0, 0, 0, 1);

		GUIManager::Instance().Render(1);
		SceneManager::Instance().LoadNewScene("MainScene");
	}

	Scene::LogicUpdate();
}

