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
	m.LoadVec3("color", glm::vec3(1, 0, 0));
	m.SetShader(AssetLoader::Instance().GetAsset<Shader>("ColorOnly"));
	MeshRenderer* mr = new MeshRenderer(qm, m);
	quad->AddComponent(mr);

	QuadMesh* qm2 = new QuadMesh();
	GameObject* quad2 = new GameObject("Quad");
	Material m2;
	m2.LoadVec3("color", glm::vec3(0, 1, 0));
	m2.SetShader(AssetLoader::Instance().GetAsset<Shader>("ColorOnly"));
	MeshRenderer* mr2 = new MeshRenderer(qm2, m2);
	quad2->AddComponent(mr2);
	quad2->transform.SetPosition(5, 0, 0);

	float ar = Window::Instance().GetAspectRatio();
	cam = new CameraPerspective(60.0f, Window::Instance().GetAspectRatio(), 0.1f, 1000.0f);
	cam->transform.SetPosition(0, 0, 30);
	//cam->transform.SetRotation(0, 180, 0);
	//cam->transform.LookAt(0, 0, 0);
	cam->transform.RotateBy(180, glm::vec3(0, 1, 0));


	AddGameObject(quad); //Add objects to scene
	AddGameObject(quad2); //Add objects to scene

	AddGameObject(cam);

	quad->AddChild(quad2);

}
void TestScene1::LogicUpdate() {

	Logger::LogInfo("Test scene 1 update");

	//quad->transform.Translate(0.1f, 0.0f, 0.0f);
	quad->transform.RotateBy(0.5f, glm::vec3(0, 1, 0));
	
	Scene::LogicUpdate();

}
void TestScene1::EngineUpdate() {
	//Scene::EngineUpdate();
}
