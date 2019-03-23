#include "Components\MeshRenderer.h"
#include "Core\CameraPerspective.h"
#include "TestScene2.h"
#include "Core/Logger.h"
#include "Scene/SceneManager.h"
#include "Prefabs\Quad.h"
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
	

	QuadMesh* qm2 = new QuadMesh();
	GameObject* quad2 = new GameObject("Quad");
	Material m2;
	m2.LoadVec3("color", 0, 1, 0); //0 1 0->RGB(so, green color)
	m2.SetShader(AssetLoader::Instance().GetAsset<Shader>("ColorOnly"));
	MeshRenderer* mr2 = new MeshRenderer(qm2, m2);
	quad2->AddComponent(mr2);
	quad2->transform.SetPosition(5, 0, 0);

	float ar = Window::Instance().GetAspectRatio();
	GameObject* cam = new CameraPerspective(60.0f, Window::Instance().GetAspectRatio(), 0.1f, 1000.0f);
	cam->transform.SetPosition(0, 0, 30);
	cam->transform.RotateBy(180, 0, 1, 0);



	AddGameObject(quad2); //Add objects to scene

	AddGameObject(cam);


}
void TestScene2::LogicUpdate() {
	//Logger::LogInfo("Updating scene", name);

	Scene::LogicUpdate();
}
void TestScene2::EngineUpdate() {
	//Scene::EngineUpdate();
}
void TestScene2::LateUpdate() {
	Scene::LateUpdate();
}