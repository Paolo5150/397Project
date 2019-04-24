#include "Components\MeshRenderer.h"
#include "Core\CameraPerspective.h"
#include "MainMenu.h"
#include "Core/Logger.h"
#include "Scene/SceneManager.h"

#include "Core\Window.h"
#include "Utils\AssetLoader.h"
#include "GUI\GUIElements\GUIManager.h"
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

	



}
void MainMenuScene::LogicUpdate() {
	//Logger::LogInfo("Updating scene", name);

	if (Input::GetKeyPressed(GLFW_KEY_ESCAPE) || Input::GetKeyPressed(GLFW_KEY_X))
		SceneManager::Instance().LoadNewScene("ExitScene");


	if (Input::GetKeyPressed(GLFW_KEY_ENTER))
		SceneManager::Instance().LoadNewScene("MainScene");

	Scene::LogicUpdate();
}

