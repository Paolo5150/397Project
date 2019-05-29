#include "Components\MeshRenderer.h"
#include "Prefabs\Axis.h"

#include "Core\MainCamera.h"
#include "SimpleScene.h"
#include "Core/Logger.h"
#include "Scene/SceneManager.h"

#include "Core\Window.h"
#include "Utils\AssetLoader.h"
#include "Lighting\LightingManager.h"
#include "Prefabs\Water.h"
#include "Prefabs\Terrain.h"
#include "Graphics\CubeMap.h"
#include "Graphics\SkyBox.h"
#include "Utils\GameAssetFactory.h"
#include "Core\Lua.h"
#include "GUI\GUIElements\GUIText.h"
#include "GUI\GUIElements\GUIImage.h"
#include "GUI\GUIElements\GUIProgressBar.h"

#include "Components\Animator.h"

#include "GUI\GUIElements\GUIManager.h"
#include "Components\BoxCollider.h"
#include "Components\SphereCollider.h"
#include "Prefabs\Pumpkin.h"
#include "Prefabs\Crate.h"
#include "Prefabs\Barrel.h"
#include "Prefabs\Cabin.h"
#include "Prefabs\Player.h"

#include "Prefabs\GranadeLauncher.h"
#include "Utils\PathFinder.h"
#include "Graphics\RenderingEngine.h"
#include "Physics\PhysicsWorld.h"
#include "Prefabs\Player.h"
#include "Components\AIBase.h"


GameObject* crate;


SimpleScene::SimpleScene() : Scene("SimpleScene")
{

}

void SimpleScene::LoadAssets() {


	AssetLoader::Instance().LoadModel("Assets\\Models\\Pumpkin\\pumpkin.obj");	


	AssetLoader::Instance().LoadModel("Assets\\Models\\Crate\\crate.obj");

	AssetLoader::Instance().LoadModel("Assets\\Models\\GranadeLauncher\\launcher.fbx", false);
	AssetLoader::Instance().LoadModel("Assets\\Models\\Alien\\alien.fbx",false);


	AssetLoader::Instance().LoadTexture("Assets\\Models\\GranadeLauncher\\launcher.jpg");


	AssetLoader::Instance().LoadTexture("Assets\\Textures\\crate_diffuse.tga");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\crate_normal.tga");


	AssetLoader::Instance().LoadTexture("Assets\\Textures\\crate_specular.tga");


}
void SimpleScene::UnloadAssets() {
	AssetLoader::Instance().Unload<Model>();
	AssetLoader::Instance().Unload<Texture2D>();

}
void SimpleScene::QuitScene() {

	Scene::QuitScene();

}
void SimpleScene::Initialize() {

	//Terrain

	Terrain::Instance().Initialize(256);

	skybox = new Skybox(AssetLoader::Instance().GetAsset<CubeMap>("SunSet"));	

	//Timer::SetDisplayFPS(true);	


	//Lights
	LightManager::Instance().SetAmbientLight(0.5f, 0.5f, 0.2f);

	DirectionalLight* dirLight = new DirectionalLight();
	dirLight->SetDiffuseColor(1, 1, 1);
	dirLight->transform.SetRotation(45, 117, 0);
	dirLight->SetIntensity(0.9f);
	dirLight->SetDiffuseColor(1.0, 1.0, 0.8);


	DirectionalLight* dirLight2 = new DirectionalLight(false);
	dirLight2->SetDiffuseColor(1, 1, 1);
	dirLight2->transform.SetRotation(90, -120, 0);
	dirLight2->SetIntensity(0.5f);
	
	//GameObjects
	player = new Player();
	AddGameObject(player);	


	crate = AssetLoader::Instance().GetAsset<Model>("Alien")->CreateGameObject();
	crate->transform.SetScale(0.2, 0.2, 0.2);
	crate->PrintHierarchy();

	int x, y, z;
	Terrain::Instance().GetCenter(x, y, z);

	
	player->transform.SetPosition(glm::vec3(x, y, z) + glm::vec3(200, 50, 0));


	crate->transform.SetPosition(x,y,z);

	
	AddGameObject(dirLight);
	AddGameObject(dirLight2);
	AddGameObject(crate);

	AddGameObject(&Terrain::Instance());



}

void SimpleScene::Start()
{
	Scene::Start();



	RenderingEngine::godRays = 1;
}

void SimpleScene::LogicUpdate()
{
	static int index = 0;

	if (Input::GetKeyPressed(GLFW_KEY_X))
		index++;

	if (Input::GetKeyPressed(GLFW_KEY_Z))
		index--;

	crate->GetComponent<Animator>("Animator")->SetCurrentAnimation(index);


	if (Input::GetKeyPressed(GLFW_KEY_ESCAPE))
		SceneManager::Instance().LoadNewScene("ExitScene");

	Scene::LogicUpdate(); //Must be last statement!

	if (Input::GetKeyPressed(GLFW_KEY_R))
		Restart();



}

void SimpleScene::Restart()
{
	SceneManager::Instance().ReloadCurrent();

}

void SimpleScene::UpdateUI()
{

}


