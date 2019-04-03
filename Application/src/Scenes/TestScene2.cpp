#include "Components\MeshRenderer.h"
#include "Core\CameraPerspective.h"
#include "TestScene2.h"
#include "Core/Logger.h"
#include "Scene/SceneManager.h"

#include "Core\Window.h"
#include "Utils\AssetLoader.h"

TestScene2::TestScene2() : Scene("TestScene2")
{

}

void TestScene2::LoadAssets() {}
void TestScene2::UnloadAssets() {}

void TestScene2::ExitScene() {
	Scene::ExitScene();
}

void TestScene2::Initialize() {
	

	


}
void TestScene2::LogicUpdate() {
	Logger::LogInfo("Updating scene", name);

	Scene::LogicUpdate();
}
void TestScene2::EngineUpdate() {
	//Scene::EngineUpdate();
}
void TestScene2::LateUpdate() {
	Scene::LateUpdate();
}