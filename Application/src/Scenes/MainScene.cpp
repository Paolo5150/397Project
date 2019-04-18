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
#include "GUI\GUIElements\GUIManager.h"


MainCamera* cam;
int luaAssetOffset = 0;
GameObject** nanosuits;
GameObject** pumpkins;
GameObject** barrels;
GameObject** crates;
GameObject* gun;
GameObject* ship;
GameObject* cabin;
PointLight* pLight;
DirectionalLight* dirLight;
Terrain* terrain;


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

	Lua::RunLua("Scripts\\Level1.lua");

	skybox = new Skybox(AssetLoader::Instance().GetAsset<CubeMap>("SunSet"));

	Timer::SetDisplayFPS(true);
	
	//nanosuit = (GameObject*)GameAssetFactory::Instance().Create("Model", "Nanosuit");
	//GameObject* n2 = (GameObject*)GameAssetFactory::Instance().Create("Model", "Cabin");
	manual = new GUIImage(AssetLoader::Instance().GetAsset<Texture2D>("manual"), 10, 10, 80, 80, 1);
	GUIManager::Instance().AddGUIObject(manual);

	//Lights
	LightManager::Instance().SetAmbientLight(0.4f, 0.4f, 0.2f);

	dirLight = new DirectionalLight();
	dirLight->SetDiffuseColor(1, 1, 1);
	dirLight->transform.SetRotation(45, 117, 0);
	dirLight->SetIntensity(0.7f);
	dirLight->SetDiffuseColor(1.0, 1.0, 0.8);

	DirectionalLight* dirLight2 = new DirectionalLight(false);
	dirLight2->SetDiffuseColor(1, 1, 1);
	dirLight2->transform.SetRotation(90, -120, 0);
	dirLight2->SetIntensity(0.5f);

	pLight = new PointLight();
	pLight->SetDiffuseColor(1, 1, 1);
	pLight->transform.Translate(-15, 10, -15);
	pLight->SetIntensity(50.0f);


	// Uncomment this to force a wood material!
	Material mat_wood;
	mat_wood.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStatic"));

	mat_wood.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("wood"));
	mat_wood.LoadCubemap(&skybox->GetCubeMap());

	mat_wood.LoadFloat("shininess", 1000.0f);
	mat_wood.LoadFloat("reflectivness", 1.0);

	Material mat_crate;
	mat_crate.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStaticNormalMap"));
	mat_crate.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("crate_diffuse"));
	mat_crate.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("crate_normal"), TextureUniform::NORMAL0);

	Material mat_ship;
	mat_ship.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStatic"));
	mat_ship.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("shipTexture"));
	mat_ship.LoadCubemap(&skybox->GetCubeMap());

	mat_ship.LoadFloat("shininess", 1000.0f);
	mat_ship.LoadFloat("reflectivness", 0.5f);

	Material mat_cabin;
	mat_cabin.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStaticNormalMap"));
	mat_cabin.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("cabin_diffuse"));
	mat_cabin.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("cabin_normal"),TextureUniform::NORMAL0);

	

	/*n2->ApplyMaterial(mat_cabin);
	n2->transform.SetScale(100, 100,100);
	n2->transform.SetRotation(-90, 0, 0);*/


	float ar = Window::Instance().GetAspectRatio();
	/*cam = (MainCamera*)GameAssetFactory::Instance().Create("MainCamera");
	cam->transform.SetPosition(0,35, 0);
	cam->transform.SetRotation(30, 180, 0);
	cam->SetMovementSpeed(500);
	

	cam->RemoveLayerMask(Layers::GUI);*/

	//Terrain
	terrain = new Terrain(256);
	terrain->ApplyHeightMap("Assets\\Textures\\hm1.jpg");

	terrain->transform.SetScale(20 ,600, 20);
	terrain->transform.Translate(0, 0, 0);
	AddGameObject(terrain);

	//GameObjects
	cam = (MainCamera*)Lua::GetCreatedAsset(0);
	luaAssetOffset++;
	cam->transform.SetPosition(Lua::GetFloatFromStack("camX"), Lua::GetFloatFromStack("camY"), Lua::GetFloatFromStack("camZ"));
	cam->transform.SetRotation(Lua::GetFloatFromStack("camRotX"), Lua::GetFloatFromStack("camRotY"), Lua::GetFloatFromStack("camRotZ"));
	cam->SetMovementSpeed(500);
	cam->RemoveLayerMask(Layers::GUI);
	AddGameObject(cam);

	Water* w = (Water*)Lua::GetCreatedAsset(1);
	luaAssetOffset++;
	//w->meshRenderer->GetMaterial().LoadCubemap(&skybox->GetCubeMap());
	nanosuits = new GameObject*[Lua::GetIntFromStack("npc_nanosuits")];
	for (int i = 0; i < Lua::GetIntFromStack("npc_nanosuits"); i++)
	{
		nanosuits[i] = (GameObject*)Lua::GetCreatedAsset(i + luaAssetOffset);
		AddGameObject(nanosuits[i]);
		nanosuits[i]->transform.SetScale(Lua::GetFloatFromStack("nanosuitScale"), Lua::GetFloatFromStack("nanosuitScale"), Lua::GetFloatFromStack("nanosuitScale"));
		float posX = Lua::GetFloatFromStack("nanosuit" + std::to_string(i + 1) + "X");
		float posY = Lua::GetFloatFromStack("nanosuit" + std::to_string(i + 1) + "Y");
		float posZ = Lua::GetFloatFromStack("nanosuit" + std::to_string(i + 1) + "Z");
		nanosuits[i]->transform.SetPosition(posX, terrain->GetHeightAt(posX, posZ) + posY, posZ);
	}
	luaAssetOffset += Lua::GetIntFromStack("npc_nanosuits");

	pumpkins = new GameObject*[Lua::GetIntFromStack("npc_pumpkins")];
	for (int i = 0; i < Lua::GetIntFromStack("npc_pumpkins"); i++)
	{
		pumpkins[i] = (GameObject*)Lua::GetCreatedAsset(i + luaAssetOffset);
		AddGameObject(pumpkins[i]);
		pumpkins[i]->transform.SetScale(Lua::GetFloatFromStack("pumpkinScale"), Lua::GetFloatFromStack("pumpkinScale"), Lua::GetFloatFromStack("pumpkinScale"));
		float posX = Lua::GetFloatFromStack("pumpkin" + std::to_string(i + 1) + "X");
		float posY = Lua::GetFloatFromStack("pumpkin" + std::to_string(i + 1) + "Y");
		float posZ = Lua::GetFloatFromStack("pumpkin" + std::to_string(i + 1) + "Z");
		pumpkins[i]->transform.SetPosition(posX, terrain->GetHeightAt(posX, posZ) + posY, posZ);
	}
	luaAssetOffset += Lua::GetIntFromStack("npc_pumpkins");

	barrels = new GameObject*[Lua::GetIntFromStack("prop_barrels")];
	for (int i = 0; i < Lua::GetIntFromStack("prop_barrels"); i++)
	{
		barrels[i] = (GameObject*)Lua::GetCreatedAsset(i + luaAssetOffset);
		AddGameObject(barrels[i]);
		barrels[i]->transform.SetScale(Lua::GetFloatFromStack("barrelScale"), Lua::GetFloatFromStack("barrelScale"), Lua::GetFloatFromStack("barrelScale"));
		float posX = Lua::GetFloatFromStack("barrel" + std::to_string(i + 1) + "X");
		float posY = Lua::GetFloatFromStack("barrel" + std::to_string(i + 1) + "Y");
		float posZ = Lua::GetFloatFromStack("barrel" + std::to_string(i + 1) + "Z");
		barrels[i]->transform.SetPosition(posX, terrain->GetHeightAt(posX, posZ) + posY, posZ);
	}
	luaAssetOffset += Lua::GetIntFromStack("prop_barrels");

	crates = new GameObject*[Lua::GetIntFromStack("prop_crates")];
	for (int i = 0; i < Lua::GetIntFromStack("prop_crates"); i++)
	{
		crates[i] = (GameObject*)Lua::GetCreatedAsset(i + luaAssetOffset);
		crates[i]->ApplyMaterial(mat_crate);
		AddGameObject(crates[i]);
		crates[i]->transform.SetScale(Lua::GetFloatFromStack("crateScale"), Lua::GetFloatFromStack("crateScale"), Lua::GetFloatFromStack("crateScale"));
		float posX = Lua::GetFloatFromStack("crate" + std::to_string(i + 1) + "X");
		float posY = Lua::GetFloatFromStack("crate" + std::to_string(i + 1) + "Y");
		float posZ = Lua::GetFloatFromStack("crate" + std::to_string(i + 1) + "Z");
		crates[i]->transform.SetPosition(posX, terrain->GetHeightAt(posX, posZ) + posY, posZ);
	}
	luaAssetOffset += Lua::GetIntFromStack("prop_crates");

	gun = (GameObject*)Lua::GetCreatedAsset(luaAssetOffset);
	AddGameObject(gun);
	gun->transform.SetScale(Lua::GetFloatFromStack("gunScale"), Lua::GetFloatFromStack("gunScale"), Lua::GetFloatFromStack("gunScale"));
	gun->transform.SetPosition(Lua::GetFloatFromStack("gunX"), terrain->GetHeightAt(Lua::GetFloatFromStack("gunX"), Lua::GetFloatFromStack("gunZ")) + Lua::GetFloatFromStack("gunY"), Lua::GetFloatFromStack("gunZ"));
	gun->transform.SetRotation(0, 0, 90);
	luaAssetOffset++;

	ship = (GameObject*)Lua::GetCreatedAsset(luaAssetOffset);
	ship->ApplyMaterial(mat_ship);
	AddGameObject(ship);
	ship->transform.SetScale(Lua::GetFloatFromStack("shipScale"), Lua::GetFloatFromStack("shipScale"), Lua::GetFloatFromStack("shipScale"));
	ship->transform.SetPosition(Lua::GetFloatFromStack("shipX"), terrain->GetHeightAt(Lua::GetFloatFromStack("shipX"), Lua::GetFloatFromStack("shipZ")) + Lua::GetFloatFromStack("shipY"), Lua::GetFloatFromStack("shipZ"));
	luaAssetOffset++;

	cabin = (GameObject*)Lua::GetCreatedAsset(luaAssetOffset);
	cabin->ApplyMaterial(mat_cabin);
	AddGameObject(cabin);
	cabin->transform.SetScale(Lua::GetFloatFromStack("cabinScale"), Lua::GetFloatFromStack("cabinScale"), Lua::GetFloatFromStack("cabinScale"));
	cabin->transform.SetPosition(Lua::GetFloatFromStack("cabinX"), terrain->GetHeightAt(Lua::GetFloatFromStack("cabinX"), Lua::GetFloatFromStack("cabinZ")) + Lua::GetFloatFromStack("cabinY"), Lua::GetFloatFromStack("cabinZ"));
	cabin->transform.SetRotation(-90, 0, 0);
	luaAssetOffset++;

	AddGameObject(w);

	AddGameObject(dirLight);
	AddGameObject(dirLight2);

	AddGameObject(pLight);
	Axis* a = new Axis();
	a->transform.SetScale(10, 10, 10);
	AddGameObject(a);
	AddGameObject(cam);
	//AddGameObject(nanosuit);
	//AddGameObject(n2);


	int x, y, z;
	terrain->GetCenter(x, y, z);
	cam->transform.SetPosition(x, y,z);

	//nanosuit->transform.SetPosition(x, terrain->GetHeightAt(x,z+500) + 4, z+500);

	//n2->transform.SetPosition(x+300, terrain->GetHeightAt(x+300, z + 1200) + 50, z + 1200);
	cam->AddChild(pLight);
	//pLight->transform.SetPosition(0, 0, 10);

	w->transform.SetPosition(x, 100, z);
	w->transform.SetScale(3000, 3000, 1);

	Lua::CloseLua();
	cam->transform.SetRotation(0, 0, 0);
}
void MainScene::LogicUpdate() {

	/*glm::vec3 toCam = glm::vec3(cam->transform.GetPosition().x, nanosuit->transform.GetPosition().y, cam->transform.GetPosition().z) - nanosuit->transform.GetPosition();
	float yAngle = glm::degrees(glm::angle(nanosuit->transform.GetLocalFront(),glm::normalize(toCam)));
	glm::vec3 cross = glm::normalize(glm::cross(nanosuit->transform.GetLocalFront(), glm::normalize(toCam)));
	int s = glm::sign(cross.y);


	glm::vec3 np = nanosuit->transform.GetPosition();
	np += nanosuit->transform.GetLocalFront() * 0.5f;
	float y = terrain->GetHeightAt(np.x, np.z);
	nanosuit->transform.SetPosition(np.x, y, np.z);*/


	/*pLight->transform.Translate(0.05f, 0, 0);
	nanosuit->transform.RotateBy(0.51f, 0,1,0);*/

	if (!cam->IsTopView())
	{
		float h = terrain->GetHeightAt(cam->transform.GetPosition().x, cam->transform.GetPosition().z);
		cam->transform.SetPosition(cam->transform.GetPosition().x, h + 30, cam->transform.GetPosition().z);

		// Limit camera position within terrain
		if (cam->transform.GetPosition().x > terrain->GetTerrainMaxX() - 50)
			cam->transform.SetPosition(terrain->GetTerrainMaxX() - 50, cam->transform.GetPosition().y, cam->transform.GetPosition().z);
		else if (cam->transform.GetPosition().x < terrain->GetTerrainMinX() + 50)
			cam->transform.SetPosition(terrain->GetTerrainMinX() + 50, cam->transform.GetPosition().y, cam->transform.GetPosition().z);

		if (cam->transform.GetPosition().z > terrain->GetTerrainMaxZ() - 50)
			cam->transform.SetPosition(cam->transform.GetPosition().x, cam->transform.GetPosition().y, terrain->GetTerrainMaxZ() - 50);
		if (cam->transform.GetPosition().z < terrain->GetTerrainMinZ() + 50)
			cam->transform.SetPosition(cam->transform.GetPosition().x, cam->transform.GetPosition().y, terrain->GetTerrainMinZ() + 50);
	}

	else
	{
		int x, y, z;
		terrain->GetCenter(x, y, z);
		cam->transform.LookAt(x, y, z);
	}	

	if (Input::GetKeyPressed(GLFW_KEY_M))
		manual->isActive = !manual->isActive;


	if (Input::GetKeyPressed(GLFW_KEY_ESCAPE) || Input::GetKeyPressed(GLFW_KEY_X))
		SceneManager::Instance().LoadNewScene("ExitScene");


	Scene::LogicUpdate(); //Must be last statement!
}

