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

}
void TestScene2::UnloadAssets() {}

void TestScene2::ExitScene() {
	Scene::ExitScene();
}

void TestScene2::Initialize() {

	 pName = new GUIText("Paolo Ferri",10,10,0.2,0.2,0.2);
	 pImage = new GUIImage(AssetLoader::Instance().GetAsset<Texture2D>("paolo"), 50, 50, 100, 100);
	 
	 GUIManager::Instance().AddGUIObject(pName);
	 GUIManager::Instance().AddGUIObject(pImage);

	

	


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