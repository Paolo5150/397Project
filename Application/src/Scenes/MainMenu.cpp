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

	Input::SetCursorMode("normal");
	GUIManager::Instance().AddGUIObject(new GUIButton("tet", "Click me", []{ 
		
		GUIManager::Instance().SetBackgroundColor(0, 0, 0, 0.0);
		GUIManager::Instance().Render(1);
		SceneManager::Instance().LoadNewScene("MainScene"); 
	
	},"",10,10,45,45,1,1,1,1));
	//GUIManager::Instance().AddGUIObject(new GUIText("paoloText", "Paolo Ferri", "invasionFont", 10, 60, 0.1f, 0.1f, 0.1f, true));



}
void MainMenuScene::LogicUpdate() {
	//Logger::LogInfo("Updating scene", name);

	if (Input::GetKeyPressed(GLFW_KEY_ESCAPE) || Input::GetKeyPressed(GLFW_KEY_X))
		SceneManager::Instance().LoadNewScene("ExitScene");


	if (Input::GetKeyPressed(GLFW_KEY_ENTER))
	{
		GUIManager::Instance().SetBackgroundColor(0, 0, 0, 0);
		GUIManager::Instance().Render(1);
		SceneManager::Instance().LoadNewScene("MainScene");
	}

	Scene::LogicUpdate();
}

