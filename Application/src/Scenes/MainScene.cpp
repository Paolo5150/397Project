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

#include "GUI\GUIElements\GUIText.h"
#include "GUI\GUIElements\GUIManager.h"


MainCamera* cam;
GameObject* nanosuit;
PointLight* pLight;
DirectionalLight* dirLight;
Terrain* terrain;


MainScene::MainScene() : Scene("MainScene")
{

}

void MainScene::LoadAssets() {

	AssetLoader::Instance().LoadModel("Assets\\Models\\Nanosuit\\nanosuit.obj");
	AssetLoader::Instance().LoadModel("Assets\\Models\\Cabin\\cabin.fbx");

	AssetLoader::Instance().LoadTexture("Assets\\Textures\\wood.jpg");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\cabin_diffuse.png");

	
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

	skybox = new Skybox(AssetLoader::Instance().GetAsset<CubeMap>("SunSet"));

	Timer::SetDisplayFPS(true);
	
	nanosuit = (GameObject*)GameAssetFactory::Instance().Create("Model", "Nanosuit");
	GameObject* n2 = (GameObject*)GameAssetFactory::Instance().Create("Model", "Cabin");



	//Lights
	LightManager::Instance().SetAmbientLight(0.2f, 0.2f, 0.1f);

	dirLight = new DirectionalLight();
	dirLight->SetDiffuseColor(1, 1, 1);
	dirLight->transform.SetRotation(25, 117, 0);
	dirLight->SetIntensity(0.7f);
	dirLight->SetDiffuseColor(1.0, 1.0, 0.8);

	DirectionalLight* dirLight2 = new DirectionalLight(false);
	dirLight2->SetDiffuseColor(1, 1, 1);
	dirLight2->transform.SetRotation(90, -120, 0);
	dirLight2->SetIntensity(0.5f);


	pLight = new PointLight();
	pLight->SetDiffuseColor(1, 1, 1);
	pLight->transform.Translate(-15, 10, -15);
	pLight->SetIntensity(10.0f);


	// Uncomment this to force a wood material!
	Material mat;
	mat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStatic"));

	mat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("wood"));
	mat.LoadCubemap(&skybox->GetCubeMap());

	mat.LoadFloat("shininess", 1000.0f);
	mat.LoadFloat("reflectivness", 1.0);

	nanosuit->ApplyMaterial(mat);
	nanosuit->ApplyColor(1, 1, 1);

	nanosuit->transform.SetScale(2,2,2);

	Material cabinMat;
	cabinMat.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStatic"));
	cabinMat.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("cabin_diffuse"));
	n2->ApplyMaterial(cabinMat);
	n2->transform.SetScale(100, 100,100);
	n2->transform.SetRotation(-90, 0, 0);


	float ar = Window::Instance().GetAspectRatio();
	cam = (MainCamera*)GameAssetFactory::Instance().Create("MainCamera");
	cam->transform.SetPosition(0,35, 0);
	cam->transform.SetRotation(30, 180, 0);
	cam->SetMovementSpeed(500);
	
	//cam->transform.LookAt(nanosuit->transform.GetPosition());
	cam->RemoveLayerMask(Layers::GUI);

	Water* w = (Water*)GameAssetFactory::Instance().Create("Water");
	terrain = new Terrain(256);
	terrain->ApplyHeightMap("Assets\\Textures\\hm1.jpg");
	//terrain->GenerateFaultFormation(64, 0, 40, 0.5f, 1);
	terrain->transform.SetScale(20 ,600, 20);
	terrain->transform.Translate(0, 0, 0);

	AddGameObject(w);

	AddGameObject(dirLight);
	AddGameObject(dirLight2);

	AddGameObject(pLight);
	Axis* a = new Axis();
	a->transform.SetScale(10, 10, 10);
	AddGameObject(a);
	AddGameObject(cam);
	AddGameObject(terrain);
	AddGameObject(nanosuit);
	AddGameObject(n2);


	int x, y, z;
	terrain->GetCenter(x, y, z);
	cam->transform.SetPosition(x, y,z);

	nanosuit->transform.SetPosition(x, terrain->GetHeightAt(x,z+500) + 4, z+500);

	n2->transform.SetPosition(x, terrain->GetHeightAt(x, z + 1500) + 4, z + 1500);


	w->transform.SetPosition(x, 100, z);
	w->transform.SetScale(3000, 3000, 1);


}
void MainScene::LogicUpdate() {

	/*glm::vec3 toCam = glm::vec3(cam->transform.GetPosition().x, nanosuit->transform.GetPosition().y, cam->transform.GetPosition().z) - nanosuit->transform.GetPosition();
	float yAngle = glm::degrees(glm::angle(nanosuit->transform.GetLocalFront(),glm::normalize(toCam)));
	glm::vec3 cross = glm::normalize(glm::cross(nanosuit->transform.GetLocalFront(), glm::normalize(toCam)));
	int s = glm::sign(cross.y);

	nanosuit->transform.RotateBy(yAngle * s, 0,1,0);

	glm::vec3 np = nanosuit->transform.GetPosition();
	np += nanosuit->transform.GetLocalFront() * 0.5f;
	float y = terrain->GetHeightAt(np.x, np.z);
	nanosuit->transform.SetPosition(np.x, y, np.z);


	pLight->transform.Translate(0.05f, 0, 0);*/
	//float h = terrain->GetHeightAt(cam->transform.GetPosition().x, cam->transform.GetPosition().z);

//	cam->transform.SetPosition(cam->transform.GetPosition().x, h + 30, cam->transform.GetPosition().z);

	if (cam->transform.GetPosition().x > terrain->GetTerrainMaxX() - 50)
		cam->transform.SetPosition(terrain->GetTerrainMaxX() - 50, cam->transform.GetPosition().y, cam->transform.GetPosition().z);
	else if (cam->transform.GetPosition().x < terrain->GetTerrainMinX() + 50)
		cam->transform.SetPosition(terrain->GetTerrainMinX() + 50, cam->transform.GetPosition().y, cam->transform.GetPosition().z);

	if (cam->transform.GetPosition().z > terrain->GetTerrainMaxZ() - 50)
		cam->transform.SetPosition(cam->transform.GetPosition().x, cam->transform.GetPosition().y, terrain->GetTerrainMaxZ() - 50);
	if (cam->transform.GetPosition().z < terrain->GetTerrainMinZ() + 50)
		cam->transform.SetPosition(cam->transform.GetPosition().x, cam->transform.GetPosition().y, terrain->GetTerrainMinZ() + 50);

	if (Input::GetKeyPressed(GLFW_KEY_ESCAPE) || Input::GetKeyPressed(GLFW_KEY_X))
		SceneManager::Instance().LoadNewScene("ExitScene");


	Scene::LogicUpdate(); //Must be last statement!
}

