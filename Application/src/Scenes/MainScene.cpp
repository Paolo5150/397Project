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
#include "GUI\GUIElements\GUIProgressBar.h"
#include "GUI\GUIElements\GUIButton.h"
#include "Prefabs\Companion.h"

#include "Components\Animator.h"

#include "GUI\GUIElements\GUIManager.h"
#include "Components\BoxCollider.h"
#include "Components\SphereCollider.h"
#include "Prefabs\Pumpkin.h"
#include "Prefabs\Crate.h"
#include "Prefabs\Barrel.h"
#include "Prefabs\Cabin.h"
#include "Prefabs\Hive.h"
#include "Prefabs\Player.h"
#include "Prefabs\Companion.h"

#include "Prefabs\PumpkinBunch.h"
#include "Prefabs\GranadeLauncher.h"
#include "Utils\PathFinder.h"
#include "Graphics\RenderingEngine.h"
#include "Physics\PhysicsWorld.h"
#include "Prefabs\Player.h"
#include "Prefabs\Spider.h"
#include "Components\AIBase.h"
#include "Utils\SaveGameManager.h"

MainCamera* cam;
bool reinit = false;


MainScene::MainScene() : Scene("MainScene")
{

}

void MainScene::LoadAssets() {




	AssetLoader::Instance().LoadTexture("Assets\\Textures\\manual.jpg");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\crate_diffuse.tga");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\crate_normal.tga");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\pumpkinIcon.png");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\shipTexture.png");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\cabin_diffuse.png");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\cabin_normal.png");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\hive_diffuse.jpg");
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\hive_normal.jpg");
}
void MainScene::UnloadAssets() {
	AssetLoader::Instance().Unload<Model>();
	AssetLoader::Instance().Unload<Texture2D>();

}
void MainScene::QuitScene() {
	PathFinder::Instance().DeleteNodes();

	Scene::QuitScene();

}
void MainScene::Initialize() {

	//Terrain

	Terrain::Instance().Initialize(256);
	//Terrain::Instance().Initialize(512);

	skybox = new Skybox(AssetLoader::Instance().GetAsset<CubeMap>("SunSet"));

	if (SaveGameManager::loadWhenPossible == true)
	{
		SaveGameManager::LoadGame();

		for (int i = 0; i < GetGameobjectsByName("Enemy_Spider").size(); i++)
		{
			((AIBase*)((Spider*)GetGameobjectsByName("Enemy_Spider").at(i))->GetComponent<AIBase>("AIBase"))->SetTarget(((Player*)GetGameobjectsByName("Player").at(0))->transform);
		}
	}

	//Timer::SetDisplayFPS(true);

	manual = new GUIImage("manualImage", AssetLoader::Instance().GetAsset<Texture2D>("manual"), 10, 10, 80, 80, 1);
	manual->isActive = 0;
	GUIManager::Instance().AddGUIObject(manual);

	// HUD elements
	pumpkinAmmoText = new GUIText("ammoText", "X 50", "invasionFont", 1, 85, 5, 1, 1, 1, 1);
	spidersLeftText = new GUIText("spiderLeftText", "", "invasionFont", 1, 80, 10, 1, 1, 1, 1);
	hivesLeftText = new GUIText("hivesLeftText", "", "invasionFont", 1, 80, 13, 1, 1, 1, 1);

	spidersKilledText = new GUIText("spidersKilledText", "", "invasionFont", 2, 35, 20, 1, 1, 1, 1);
	pumpkinsShotText = new GUIText("pumpkinsShotText", "", "invasionFont", 2, 35, 30, 1, 1, 1, 1);

	pumpkinAmmoImage = new GUIImage("pumpkinIcon", AssetLoader::Instance().GetAsset<Texture2D>("pumpkinIcon"), 80, 3, 7, 7, 1);
	endGameText = new GUIText("EndGameText", "", "invasionFont", 2, 35, 10, 1, 1, 1, 1);
	endGameText->isActive = 0;

	centerText = new GUIText("centerText", "", "arcadeFont", 1, 25, 50, 1, 1, 1, 1);
	centerText->position.x = 5;
	centerText->CalculateSizePosition();
	centerText->isActive = 0;

	resumeButton = (new GUIButton("ResumeButton", "Resume", [&] {

		Resume();

	}, "", 1.5, 10, 10, 45, 15, 1, 1, 1, 1));

	saveButton = (new GUIButton("SaveButton", "Save", [&] {

		centerText->isActive = 1;
		if (player->hasGun == true)
		{
			SaveGameManager::SaveGame();
			if (SaveGameManager::CanLoadGame())
			{
				centerText->_message = "Save Successful!";
			}
			else
			{

				centerText->_message = "Save Failed!";
			}
		}
		else
		{

			centerText->_message = "Collect the gun before saving!";
		}

	}, "", 1.5, 10, 10, 45, 30, 1, 1, 1, 1));

	restartButton = (new GUIButton("RestartButton", "Restart", [&] {

		Input::SetCursorMode("disabled");
		GUIManager::Instance().SetBackgroundColor(0, 0, 0, 0);
		Restart();

	}, "", 1.5, 10, 10, 45, 45, 1, 1, 1, 1));

	quitToMenuButton = (new GUIButton("QuitToMenuButton", "Menu", [&] {

		GUIManager::Instance().SetBackgroundColor(0, 0, 0, 0);
		SceneManager::Instance().LoadNewScene("MainMenuScene");

	}, "", 1.5, 10, 10, 45, 60, 1, 1, 1, 1));

	quitToDesktopButton = (new GUIButton("QuitButton", "Quit", [&] {

		GUIManager::Instance().SetBackgroundColor(0, 0, 0, 0);
		SceneManager::Instance().LoadNewScene("ExitScene");

	}, "", 1.5, 10, 10, 45, 75, 1, 1, 1, 1));

	restartButton->isActive = 0;
	saveButton->isActive = 0;
	quitToDesktopButton->isActive = 0;
	quitToMenuButton->isActive = 0;
	resumeButton->isActive = 0;

	GUIManager::Instance().AddGUIObject(pumpkinAmmoText);
	GUIManager::Instance().AddGUIObject(pumpkinAmmoImage);
	GUIManager::Instance().AddGUIObject(endGameText);
	GUIManager::Instance().AddGUIObject(spidersLeftText);
	GUIManager::Instance().AddGUIObject(hivesLeftText);
	GUIManager::Instance().AddGUIObject(spidersKilledText);
	GUIManager::Instance().AddGUIObject(pumpkinsShotText);
	GUIManager::Instance().AddGUIObject(centerText);

	GUIManager::Instance().AddGUIObject(restartButton);
	GUIManager::Instance().AddGUIObject(saveButton);
	GUIManager::Instance().AddGUIObject(quitToDesktopButton);
	GUIManager::Instance().AddGUIObject(quitToMenuButton);
	GUIManager::Instance().AddGUIObject(resumeButton);

	healthBar = new GUIProgressBar("", "", 3, 3, 40, 3, 1);
	GUIManager::Instance().AddGUIObject(healthBar);

	//Lights
	LightManager::Instance().SetAmbientLight(0.7f, 0.7f, 0.4f);

	DirectionalLight* dirLight = new DirectionalLight();
	dirLight->SetDiffuseColor(1, 1, 1);
	dirLight->transform.SetRotation(45, 117, 0);
	dirLight->SetIntensity(0.9f);
	dirLight->SetDiffuseColor(1.0, 1.0, 0.8);


	DirectionalLight* dirLight2 = new DirectionalLight(false);
	dirLight2->SetDiffuseColor(1, 1, 1);
	dirLight2->transform.SetRotation(90, -120, 0);
	dirLight2->SetIntensity(0.5f);

	PathFinder::Instance().Generate(&Terrain::Instance());
	/*for (unsigned i = 0; i < PathFinder::Instance().pathNodes.size(); i++)
		AddGameObject(PathFinder::Instance().pathNodes[i]);*/

	//GameObjects
	Lua::RunLua("Assets\\Scripts\\Level1.lua", false, true);
	for (int i = 0; i < Lua::GetCreatedAssetLength(); i++) //Loop through all the game objects and add them to the scene
	{
		GameObject* obj = (GameObject*)Lua::GetCreatedAsset(i);
		if (!(SaveGameManager::loadWhenPossible == true && SaveGameManager::IsSaveable(obj->GetName())))
		{
			if (obj->HasComponent("AIBase")) //If the object has an ai component, set its target to the player (Warning: Player must be created before any AI)
			{
				((AIBase*)obj->GetComponent<AIBase>("AIBase"))->SetTarget(((Player*)GetGameobjectsByName("Player").at(0))->transform);
			}
			AddGameObject(obj);
		}
	}
	Lua::CloseLua();

	player = ((Player*)GetGameobjectsByName("Player").at(0));

	if (SaveGameManager::loadWhenPossible == false)
	{
		Companion* comp = new Companion();
		comp->transform.SetPosition(player->transform.GetPosition() + glm::vec3(200, -20, 0));
		AddGameObject(comp);
	}

	int x, y, z;
	Terrain::Instance().GetCenter(x, y, z);
	PhysicsWorld::Instance().InitializeQuadtree(x, z, Terrain::Instance().GetTerrainMaxX() - Terrain::Instance().GetTerrainMinX(), Terrain::Instance().GetTerrainMaxZ() - Terrain::Instance().GetTerrainMinZ());

	AddGameObject(dirLight);
	AddGameObject(dirLight2);
	AddGameObject(&Terrain::Instance());


	//Randomly spawn the gun
	
	if (SaveGameManager::loadWhenPossible == false)
	{
		Player::ResetTotalPumpkinShots();
		Spider::ResetTotalSpidersKilled();
	}
	currentSceneState = PLAYING;

	SaveGameManager::loadWhenPossible = false;
}

void MainScene::Start()
{
	Scene::Start();

	PathFinder::Instance().Start();

	PhysicsWorld::Instance().FillQuadtree(true);
	PhysicsWorld::Instance().PerformCollisions(true);
	Logger::LogInfo("Nodes", PathFinder::Instance().pathNodes.size());

	companion = dynamic_cast<Companion*>(GetGameobjectsByName("Companion")[0]);

	RenderingEngine::godRays = 1;
	// Place gun
	if (player->hasGun == false)
	{
		glm::vec3 gunPos = PathFinder::Instance().GetRandomFreeNodePosition();
		GranadeLauncher* gn = new GranadeLauncher();
		gn->Start();
		gn->SetLayer(0);
		gn->spin = 1;
		gn->SetLayer(Layers::DEFAULT);
		gn->GetCollider()->transform.SetScale(100, 100, 180);
		gn->transform.SetScale(0.1, 0.1, 0.1);
		gn->transform.SetPosition(gunPos + glm::vec3(0, 50, 0));
		AddGameObject(gn);

		centerText->isActive = 1;
		centerText->position.y = 10;
		centerText->CalculateSizePosition();
		centerText->_message = "Find the gun!";
	}

	Input::SetIsEnabled(1);
}

void MainScene::LogicUpdate()
{


	PhysicsWorld::Instance().Update();

	if (currentSceneState == PLAYING)
	{
		static float textTimer = 0;
		textTimer += Timer::GetDeltaS();

		if (textTimer > 20)
		{
			centerText->isActive = 0;
			textTimer = 0;
		}

		if (companion->GetHealthComponent()->IsDead())
		{
			centerText->isActive = 1;
			centerText->position.y = 10;
			centerText->CalculateSizePosition();
			centerText->_message = "Your companion is down! Stand next to it to revive it!";

		}
		
		//Spawn bunches
		static float bunchTimer = 0;
		bunchTimer += Timer::GetDeltaS();

		if (bunchTimer >= 2 && PumpkinBunch::totalPumpkinBunches < 40)
		{
			bunchTimer = 0;
			glm::vec3 pos = PathFinder::Instance().GetRandomFreeNodePosition();
			PumpkinBunch* pb = new PumpkinBunch();
			pb->Start();
			pb->transform.SetPosition(pos);
			AddGameObject(pb);
		}

		if (player->healthComponent->IsDead())
		{
			currentSceneState = GAMEOVER;
		}

		if (Hive::totalHives == 0 && Spider::GetTotalSpiders() == 0)
		{
			currentSceneState = WIN;
		}

		UpdateUI();

		if (Input::GetKeyPressed(GLFW_KEY_M))
			manual->isActive = !manual->isActive;

		Scene::LogicUpdate(); //Must be last statement!

		if (Input::GetKeyPressed(GLFW_KEY_R))
			Restart();


		if (Input::GetKeyPressed(GLFW_KEY_ESCAPE) || Input::GetKeyPressed(GLFW_KEY_X))
		{
			currentSceneState = PAUSE;
			Input::SetCursorMode("normal");
			GUIManager::Instance().SetBackgroundColor(0, 0, 0, 0.5);
			DisplayPauseMenu();

		}

	}
	else if (currentSceneState == PAUSE)
	{
		
		if (Input::GetKeyPressed(GLFW_KEY_ESCAPE) || Input::GetKeyPressed(GLFW_KEY_X))
		{
			Resume();
		}

	}
	else if (currentSceneState == WIN)
	{
		endGameText->_message = "YOU WIN!";
		DisplayEndGameMenu();
	}
	else if (currentSceneState == GAMEOVER)
	{

		endGameText->_message = "YOU'RE DEAD!";
		DisplayEndGameMenu();

	}
}

void MainScene::DisplayPauseMenu()
{
	Input::SetCursorMode("normal");
	restartButton->isActive = 1;
	saveButton->isActive = 1;
	quitToDesktopButton->isActive = 1;
	quitToMenuButton->isActive = 1;
	resumeButton->isActive = 1;
	centerText->isActive = 0;
}

void MainScene::Resume()
{
	GUIManager::Instance().SetBackgroundColor(0, 0, 0, 0);
	Input::SetCursorMode("disabled");
	centerText->isActive = 0;
	restartButton->isActive = 0;
	saveButton->isActive = 0;
	quitToDesktopButton->isActive = 0;
	quitToMenuButton->isActive = 0;
	resumeButton->isActive = 0;
	currentSceneState = PLAYING;
}



void MainScene::DisplayEndGameMenu()
{
	centerText->isActive = 0;
	pumpkinAmmoImage->isActive = false;
	healthBar->isActive = false;
	pumpkinAmmoText->isActive = 0;
	endGameText->isActive = 1;
	spidersLeftText->isActive = 0;
	hivesLeftText->isActive = 0;
	GUIManager::Instance().SetBackgroundColor(0, 0, 0, 1);
	Input::SetCursorMode("normal");

	std::stringstream ss;
	ss << "Spiders killed: ";
	ss << Spider::GetTotalSpidersKilled();
	spidersKilledText->_message = ss.str();

	ss.str("");
	ss << "Pumpkins shot: ";
	ss << Player::GetTotalPumpkinsShot();
	pumpkinsShotText->_message = ss.str();

	restartButton->isActive = 1;
	quitToDesktopButton->isActive = 1;
	quitToMenuButton->isActive = 1;


}


void MainScene::Restart()
{
	Input::SetIsEnabled(0);

	SceneManager::Instance().ReloadCurrent();

}

void MainScene::UpdateUI()
{
	std::stringstream ss;
	if (player != nullptr)
	{
		ss << "x ";
		ss << player->GetAmmos();
		pumpkinAmmoText->_message = ss.str();
		healthBar->percentage = player->healthComponent->GetHealthMaxRatio();
	}

	ss.str("");
	ss << "Spiders: ";
	ss << Spider::GetTotalSpiders();
	spidersLeftText->_message = ss.str();

	ss.str("");
	ss << "Hives: ";
	ss << Hive::totalHives;
	hivesLeftText->_message = ss.str();

}


