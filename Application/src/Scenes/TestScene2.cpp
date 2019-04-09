#include "Components\MeshRenderer.h"
#include "Core\CameraPerspective.h"
#include "TestScene2.h"
#include "Core/Logger.h"
#include "Scene/SceneManager.h"

#include "Core\Window.h"
#include "Utils\AssetLoader.h"
#include "GUI\GUIElements\GUIManager.h"
#include "Core\Input.h"
#include "Event\EventDispatcher.h"
#include "Event\ApplicationEvents.h"


TestScene2::TestScene2() : Scene("TestScene2")
{

}

void TestScene2::LoadAssets() {

	AssetLoader::Instance().LoadTexture("Assets\\Textures\\paolo.png");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\dylan.png");


}
void TestScene2::UnloadAssets() {

	AssetLoader::Instance().Unload<Texture2D>();
}

void TestScene2::ExitScene() {
	Scene::ExitScene();
}

void TestScene2::Initialize() {	 

	 GUIManager::Instance().AddGUIObject(new GUIImage(AssetLoader::Instance().GetAsset<Texture2D>("paolo"), 10, 20, 25, 35, true)); 
	 GUIManager::Instance().AddGUIObject(new GUIImage(AssetLoader::Instance().GetAsset<Texture2D>("dylan"), 40, 20, 25, 35, true));

	 GUIManager::Instance().AddGUIObject(new GUIText("Paolo Ferri", 10, 60, 0.1f, 0.1f, 0.1f, true));
	 GUIManager::Instance().AddGUIObject(new GUIText("Dylan Green", 40, 60, 0.1f, 0.1f, 0.1f, true));


}
void TestScene2::LogicUpdate() {
	//Logger::LogInfo("Updating scene", name);

	if (Input::GetKeyPressed(GLFW_KEY_ESCAPE))
		EventDispatcher::Instance().DispatchEvent(new QuitRequestEvent());

	Scene::LogicUpdate();
}
void TestScene2::EngineUpdate() {
	//Scene::EngineUpdate();
}
void TestScene2::LateUpdate() {
	Scene::LateUpdate();
}