#include "Components\MeshRenderer.h"
#include "Prefabs\Axis.h"

#include "Core\MainCamera.h"
#include "MainScene.h"
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
#include "Components\Animator.h"

#include "GUI\GUIElements\GUIManager.h"
#include "Components\BoxCollider.h"
#include "Components\SphereCollider.h"
#include "Prefabs\Pumpkin.h"
#include "Prefabs\Crate.h"
#include "Prefabs\Barrel.h"
#include "Prefabs\Cabin.h"
#include "Utils\PathFinder.h"
#include "Graphics\RenderingEngine.h"


#include "Physics\PhysicsWorld.h"

#include "Components\AIBase.h"

MainCamera* cam;
PointLight* pLight;
DirectionalLight* dirLight;
btDefaultMotionState* motionstate;
btRigidBody *rigidBody;
Crate* crate;
GameObject* c1;
GameObject* c2;

MainScene::MainScene() : Scene("MainScene")
{

}

void MainScene::LoadAssets() {

	AssetLoader::Instance().LoadModel("Assets\\Models\\Nanosuit\\nanosuit.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Pumpkin\\pumpkin.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Barrel\\barrel.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Crate\\crate.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Gun\\gun.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Ship\\ship.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Cabin\\cabin.fbx");

	AssetLoader::Instance().LoadTexture("Assets\\Textures\\manual.png");
	//AssetLoader::Instance().LoadModel("Assets\\Models\\Wolf\\wolf.fbx");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Spider\\spider_3.fbx", 0);

	AssetLoader::Instance().LoadTexture("Assets\\Models\\Spider\\textures\\Spinnen_Bein_tex_COLOR_.jpg");

	AssetLoader::Instance().LoadTexture("Assets\\Textures\\wood.jpg");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\crate_diffuse.tga");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\crate_normal.tga");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\crate_specular.tga");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\shipTexture.png");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\cabin_diffuse.png");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\cabin_normal.png");
}
void MainScene::UnloadAssets() {
	AssetLoader::Instance().Unload<Model>();
	AssetLoader::Instance().Unload<Texture2D>();

}
void MainScene::QuitScene() {
	Logger::LogError("Scene asset clean up");

	Scene::QuitScene();

}
void MainScene::Initialize() {

	//Terrain
	Terrain::Instance().Initialize(256);

	skybox = new Skybox(AssetLoader::Instance().GetAsset<CubeMap>("SunSet"));

	Lua::RunLua("Assets\\Scripts\\Level1.lua");
	gContactAddedCallback = PhysicsWorld::CollisionCallback;

	Timer::SetDisplayFPS(true);

	manual = new GUIImage("manualImage", AssetLoader::Instance().GetAsset<Texture2D>("manual"), 10, 10, 80, 80, 1);
	manual->isActive = 0;
	GUIManager::Instance().AddGUIObject(manual);



	//Lights
	LightManager::Instance().SetAmbientLight(0.5f, 0.5f, 0.2f);

	dirLight = new DirectionalLight();
	dirLight->SetDiffuseColor(1, 1, 1);
	dirLight->transform.SetRotation(45, 117, 0);
	dirLight->SetIntensity(0.9f);
	dirLight->SetDiffuseColor(1.0, 1.0, 0.8);
	Logger::LogInfo("Dir light front", Maths::Vec3ToString(dirLight->transform.GetLocalFront()));

	DirectionalLight* dirLight2 = new DirectionalLight(false);
	dirLight2->SetDiffuseColor(1, 1, 1);
	dirLight2->transform.SetRotation(90, -120, 0);
	dirLight2->SetIntensity(0.5f);

	pLight = new PointLight();
	pLight->SetDiffuseColor(1, 1, 1);
	pLight->transform.Translate(-15, 10, -15);
	pLight->SetIntensity(50.0f);

	PathFinder::Instance().Generate(&Terrain::Instance());
	for (unsigned i = 0; i < PathFinder::Instance().pathNodes.size(); i++)
		AddGameObject(PathFinder::Instance().pathNodes[i]);


	//GameObjects
	cam = (MainCamera*)Lua::GetCreatedAsset(0);
	cam->SetMovementSpeed(500);
	cam->RemoveLayerMask(Layers::GUI);
	AddGameObject(cam);

	for (int i = 1; i < Lua::GetCreatedAssetLength(); i++) //Loop through all the game objects that aren't the camera or water, and add them to the scene
	{
		GameObject* obj = (GameObject*)Lua::GetCreatedAsset(i);
		if (obj->HasComponent("AIBase")) //If the object has an ai component, set its target to the player
		{
			((AIBase*)obj->GetComponent<AIBase>("AIBase"))->SetTarget(cam->transform);
		}
		AddGameObject(obj);
	}

	int x, y, z;
	Terrain::Instance().GetCenter(x, y, z);
	PhysicsWorld::Instance().InitializeQuadtree(x, z, Terrain::Instance().GetTerrainMaxX() - Terrain::Instance().GetTerrainMinX(), Terrain::Instance().GetTerrainMaxZ() - Terrain::Instance().GetTerrainMinZ());


	AddGameObject(dirLight);
	AddGameObject(dirLight2);
	AddGameObject(pLight);
	AddGameObject(&Terrain::Instance());

	Lua::CloseLua();

}

void MainScene::Start()
{
	Scene::Start();

	PathFinder::Instance().Start();

	PhysicsWorld::Instance().FillQuadtree(true);
	PhysicsWorld::Instance().PerformCollisions(true);
	
	RenderingEngine::godRays = 1;
}

void MainScene::LogicUpdate()
{
	PhysicsWorld::Instance().Update(Timer::GetDeltaS());

	if (Input::GetKeyPressed(GLFW_KEY_M))
		manual->isActive = !manual->isActive;


	if (Input::GetKeyPressed(GLFW_KEY_ESCAPE) || Input::GetKeyPressed(GLFW_KEY_X))
		SceneManager::Instance().LoadNewScene("ExitScene");

	Scene::LogicUpdate(); //Must be last statement!

}

