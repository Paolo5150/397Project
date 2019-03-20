#include "TestScene1.h"
#include "Core/Logger.h"
#include "Scene/SceneManager.h"

TestScene1::TestScene1() : Scene("TestScene1")
{

}

void TestScene1::LoadAssets() {
	
}
void TestScene1::UnloadAssets() {
	Logger::LogInfo("Unloaded", name);
}
void TestScene1::ExitScene() {
	Logger::LogInfo("Exited", name);
}
void TestScene1::Initialize() {
	Logger::LogInfo("Initialized", name);
}
void TestScene1::LogicUpdate() {

	static float c = 0;
	
	c += Timer::GetDeltaS();

	if (c > 4)
	{
		SceneManager::Instance().LoadNewScene("TestScene2");
		return;
	}

	Logger::LogInfo("Updating scene", name);
	Logger::LogInfo("WTF");

}
void TestScene1::EngineUpdate() {}
void TestScene1::LateUpdate() {}