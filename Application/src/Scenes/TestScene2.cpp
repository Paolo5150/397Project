#include "TestScene2.h"
#include "Core/Logger.h"

TestScene2::TestScene2() : Scene("TestScene2")
{

}

void TestScene2::LoadAssets() {}
void TestScene2::UnloadAssets() {}
void TestScene2::ExitScene() {}
void TestScene2::Initialize() {
	Logger::LogInfo("Initialized", name);
}
void TestScene2::LogicUpdate() {
	Logger::LogInfo("Updating scene", name);
}
void TestScene2::EngineUpdate() {}
void TestScene2::LateUpdate() {}