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

	AssetLoader::Instance().LoadModel("Assets\\Models\\Nanosuit\\nanosuit.obj");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\wood.jpg");

	
}
void TestScene1::UnloadAssets() {
	AssetLoader::Instance().Unload<Model>();
	AssetLoader::Instance().Unload<Texture2D>();

}
void TestScene1::ExitScene() {
	Scene::ExitScene();

}
void TestScene1::Initialize() {

	QuadMesh* qm = new QuadMesh();
	quad = new GameObject("Quad");
	Material m;
	m.LoadVec3("color", 1,0,0); // 1 0 0 -> RGB (so, red color)
	m.SetShader(AssetLoader::Instance().GetAsset<Shader>("ColorOnly"));
	MeshRenderer* mr = new MeshRenderer(qm, m);
	quad->AddComponent(mr);

	QuadMesh* qm2 = new QuadMesh();
	GameObject* quad2 = new GameObject("Quad2");
	Material m2;
	m2.LoadVec3("color", 0, 1, 0); //0 1 0->RGB(so, green color)
	m2.SetShader(AssetLoader::Instance().GetAsset<Shader>("ColorOnly"));
	MeshRenderer* mr2 = new MeshRenderer(qm2, m2);
	quad2->AddComponent(mr2);
	quad2->transform.SetPosition(5, 0, 0);

	GameObject* nanosuit = AssetLoader::Instance().GetAsset<Model>("Nanosuit")->CreateGameObject();

	// Uncomment this to force a wood material!
	/*Material mat;
	mat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStatic"));
	mat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("wood"));
	nanosuit->ApplyMaterial(mat);*/
	

	float ar = Window::Instance().GetAspectRatio();
	cam = new CameraPerspective(60.0f, Window::Instance().GetAspectRatio(), 0.1f, 1000.0f);
	cam->transform.SetPosition(0, 0, 30);
	cam->transform.RotateBy(180, 0,1,0);


	AddGameObject(quad); //Add objects to scene
	AddGameObject(quad2); //Add objects to scene

	AddGameObject(cam);
	AddGameObject(nanosuit);

	quad->AddChild(quad2);
	quad2->AddChild(nanosuit);

	quad->PrintHierarchy();


}
void TestScene1::LogicUpdate() {

	//Logger::LogInfo("Test scene 1 update");

	//quad->transform.Translate(0.1f, 0.0f, 0.0f);

	quad->transform.RotateBy(0.5f, 0,1,1);	

	

	Scene::LogicUpdate(); //Must be last statement!
}
void TestScene1::EngineUpdate() {
	//Scene::EngineUpdate();
}
