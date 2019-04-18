#include "Components\MeshRenderer.h"
#include "Core\CameraPerspective.h"
#include "ExitScene.h"
#include "Core/Logger.h"
#include "Scene/SceneManager.h"

#include "Core\Window.h"
#include "Utils\AssetLoader.h"
#include "GUI\GUIElements\GUIManager.h"
#include "Core\Input.h"
#include "Event\EventDispatcher.h"
#include "Event\ApplicationEvents.h"


ExitScene::ExitScene() : Scene("ExitScene")
{

}

void ExitScene::LoadAssets() {

	AssetLoader::Instance().LoadTexture("Assets\\Textures\\paolo.png");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\dylan.png");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\mitch.png");



}
void ExitScene::UnloadAssets() {

	AssetLoader::Instance().Unload<Texture2D>();
}

void ExitScene::QuitScene() {
	Scene::QuitScene();
}

void ExitScene::Initialize() {

	 GUIManager::Instance().AddGUIObject(new GUIImage(AssetLoader::Instance().GetAsset<Texture2D>("paolo"), 10, 20, 25, 35, true)); 
	 GUIManager::Instance().AddGUIObject(new GUIImage(AssetLoader::Instance().GetAsset<Texture2D>("dylan"), 40, 20, 25, 35, true));
	 GUIManager::Instance().AddGUIObject(new GUIImage(AssetLoader::Instance().GetAsset<Texture2D>("mitch"), 70, 20, 25, 35, true));

	 GUIManager::Instance().AddGUIObject(new GUIText("Paolo Ferri", 10, 60, 0.1f, 0.1f, 0.1f, true));
	 GUIManager::Instance().AddGUIObject(new GUIText("Dylan Green", 40, 60, 0.1f, 0.1f, 0.1f, true));
	 GUIManager::Instance().AddGUIObject(new GUIText("Mitchell Hollings", 70, 60, 0.1f, 0.1f, 0.1f, true));



}
void ExitScene::LogicUpdate() {
	//Logger::LogInfo("Updating scene", name);

	if (Input::GetKeyPressed(GLFW_KEY_ESCAPE) || Input::GetKeyPressed(GLFW_KEY_X))
		EventDispatcher::Instance().DispatchEvent(new QuitRequestEvent());

	Scene::LogicUpdate();
}

