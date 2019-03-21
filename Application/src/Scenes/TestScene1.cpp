#include "Components\MeshRenderer.h"
#include "Core\CameraPerspective.h"
#include "TestScene1.h"
#include "Core/Logger.h"
#include "Scene/SceneManager.h"
#include "Prefabs\Quad.h"
#include "Core\Window.h"
#include "Utils\AssetLoader.h"




TestScene1::TestScene1() : Scene("TestScene1")
{

}

void TestScene1::LoadAssets() {




	
}
void TestScene1::UnloadAssets() {

}
void TestScene1::ExitScene() {
	Scene::ExitScene();

}
void TestScene1::Initialize() {

	QuadMesh* qm = new QuadMesh();
	quad = new GameObject("Quad");
	Material m;

	m.SetShader(AssetLoader::Instance().GetAsset<Shader>("ColorOnly"));
	MeshRenderer* mr = new MeshRenderer(qm, m);

	quad->AddComponent(mr);
	//quad->transform.SetPosition(0, 0, -20);
	float ar = Window::Instance().GetAspectRatio();
	cam = new CameraPerspective(60.0f, Window::Instance().GetAspectRatio(), 0.1f, 1000.0f);
	cam->transform.SetPosition(0, 0, 15);
	//cam->transform.SetRotation(0, 180, 0);
	//cam->transform.LookAt(0, 0, 0);
	cam->transform.RotateBy(180, glm::vec3(0, 1, 0));


	AddGameObject(quad); //Add objects to scene
	AddGameObject(cam);

}
void TestScene1::LogicUpdate() {

	Logger::LogInfo("Test scene 1 update");

	
	static float timer = 0;
	static bool done = 0;
	timer += Timer::GetDeltaS();

	if (timer > 4 && !done)
	{
		Logger::LogError("Destroy!");
		done = true;
		quad->FlagToBeDestroyed();
	}

	Scene::LogicUpdate();

}
void TestScene1::EngineUpdate() {
	//Scene::EngineUpdate();
}
