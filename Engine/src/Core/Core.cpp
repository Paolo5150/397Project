
#include "Core.h"
#include "..\Event\TimerEvents.h"
#include "Logger.h"
#include "..\Event\WindowEvents.h"
#include "..\Event\ApplicationEvents.h"

#include "..\Graphics\ShaderGL.h"
#include "..\Graphics\Texture2D.h"

#include "..\Utils\AssetLoader.h"
#include "Transform.h"
#include "..\Graphics\RenderingEngine.h"
#include "..\Lighting\LightingManager.h"
#include "Input.h"
#include "..\GUI\GUIElements\GUIManager.h"
#include <thread>
#include <stdint.h>

void Core::Initialize()
{
	Window::Initialize(); //Set context

	graphicsAPI = new API_Opengl();

	graphicsAPI->Initialize();

	//Events subscirption
	EventDispatcher::Instance().SubscribeCallback<LogicUpdateEvent>(std::bind(&Core::LogicUpdate, this, std::placeholders::_1));
	EventDispatcher::Instance().SubscribeCallback<LateUpdateEvent>(std::bind(&Core::LateUpdate, this, std::placeholders::_1));
	EventDispatcher::Instance().SubscribeCallback<RenderEvent>(std::bind(&Core::Render, this, std::placeholders::_1));
	EventDispatcher::Instance().SubscribeCallback<EngineUpdateEvent>(std::bind(&Core::EngineUpdate, this, std::placeholders::_1));

	EventDispatcher::Instance().SubscribeCallback<WindowResizeEvent>([this](Event* e){
		WindowResizeEvent* wre = dynamic_cast<WindowResizeEvent*>(e);
		GetGraphicsAPI().SetViewPort(wre->width, wre->height);
		return 0;
	});

	EventDispatcher::Instance().SubscribeCallback<QuitRequestEvent>([this](Event* e){
		m_isRunning = false;
		return 0;
	});

	//Close window, exit loop
	EventDispatcher::Instance().SubscribeCallback<WindowCloseEvent>([this](Event* event) -> bool{
		m_isRunning = 0;
		return 0; });


	//WINDOW
	// Set up windows after flew initialization (and after the context has been set).
	Window::Instance().SetWindowSize(800, 600);

	//Managers initialization
	Input::Init(false, true);
	Timer::Initialize();
	LightManager::Instance().Initialize();
	AssetLoader::Initialize(graphicsAPI);
	RenderingEngine::Instance().Initialize();
	GUIManager::Instance().Initialize();


	//Assets loaded here are available to all scenes.
	//Load textures
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\logo.png", true);

	//Splash screen
	int wx, wy;
	Window::Instance().GetWindowSize(wx, wy);

	loading = new GUIText("Loading...", 20, wy - 50, 0.2f, 0.2f, 0.2f);
	GUIManager::Instance().AddGUIObject<GUIText>(loading);
	GUIManager::Instance().AddGUIObject<GUIImage>(new GUIImage(AssetLoader::Instance().GetAsset<Texture2D>("logo"),
		0 + 50, 0 + 50,
		wx - 100, wy - 50));
	LoadBasicAssets();
	
	loading->_message = "Loading scene (and what a scene that is)...";
	GUIManager::Instance().Render(1, 1);
	//Get cpplication
	m_runningApplication = CreateApplication();
	Window::Instance().SetWindowTitle(m_runningApplication->name.c_str()); //Window title -> game title

	//Start update loop
	m_isRunning = true;
}
void Core::Run()
{
	m_runningApplication->AppInitialize();
	while (m_isRunning)
	{
		// Just update the timer
		// The timer will send out events for update, render and so on
		Window::Instance().UpdateEvents();		
		Timer::Update();		
	}
}
void Core::Shutdown()
{

	m_runningApplication->AppShutdown(); //Shutdow game first

	AssetLoader::Instance().UnloadPreserved<Shader>(); 
	AssetLoader::Instance().UnloadPreserved<Texture2D>();
	AssetLoader::Instance().UnloadPreserved<Model>();

	GUIManager::Instance().Shutdown();

	graphicsAPI->Shutdown();
	Window::Instance().Destroy();
	glfwTerminate();
}

Core& Core::Instance()
{
	static Core instance;
	return instance;
}

Core::~Core()
{
	delete graphicsAPI;
}

Core::Core()
{}

bool Core::IsRunning()
{
	return m_isRunning;
}

bool Core::LogicUpdate(Event* e)
{
	//Logger::LogInfo("Core logic update");

	m_runningApplication->AppLogicUpdate();
	return 0;
}

GraphicsAPI& Core::GetGraphicsAPI()
{
	return *graphicsAPI;
}

bool Core::EngineUpdate(Event* e)
{
	//Logger::LogInfo("Core engine update");
	m_runningApplication->AppEngineUpdate();

	return 0;
}

bool Core::LateUpdate(Event* e)
{
	//Logger::LogInfo("Core late update");

	m_runningApplication->AppLateUpdate();
	RenderingEngine::Instance().ClearRendererList();
	Input::Update();
	return 0;
}


bool Core::Render(Event* e)
{
	//Logger::LogInfo("Core rendering");

	LightManager::Instance().Update();
	RenderingEngine::Instance().RenderBuffer();
	GUIManager::Instance().Render();	

	Window::Instance().Refresh();
	return 0;
}

void Core::LoadBasicAssets()
{

	loading->_message = "Loading textures...";
	GUIManager::Instance().Render(1, 1);
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\water_normal.jpg", true);
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\rockNormal.jpg", true);
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\dudv.png", true);
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\grass.jpg", true);
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\ground.jpg", true);
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\rock.jpg", true);
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\hm1.png", true);
	AssetLoader::Instance().LoadCubeMap("Assets\\SkyBoxes\\ClearSky", true);
	AssetLoader::Instance().LoadCubeMap("Assets\\SkyBoxes\\SunSet", true);

	loading->_message = "Loading impressive shaders...";
	GUIManager::Instance().Render(1, 1);
	//Load shsders
	AssetLoader::Instance().LoadShader("ColorOnly", "Assets\\Shaders\\ColorOnly.v", "Assets\\Shaders\\ColorOnly.f", true);
	AssetLoader::Instance().LoadShader("DefaultStatic", "Assets\\Shaders\\DefaultStatic.v", "Assets\\Shaders\\DefaultStatic.f", true);
	AssetLoader::Instance().LoadShader("DefaultStaticNormalMap", "Assets\\Shaders\\DefaultStaticNormalMap.v", "Assets\\Shaders\\DefaultStaticNormalMap.f", true);
	AssetLoader::Instance().LoadShader("DefaultStaticNoLight", "Assets\\Shaders\\DefaultStaticNoLight.v", "Assets\\Shaders\\DefaultStaticNoLight.f", true);
	AssetLoader::Instance().LoadShader("Terrain", "Assets\\Shaders\\Terrain.v", "Assets\\Shaders\\Terrain.f", true);
	AssetLoader::Instance().LoadShader("Water", "Assets\\Shaders\\Water.v", "Assets\\Shaders\\Water.f", true);
	AssetLoader::Instance().LoadShader("Skybox", "Assets\\Shaders\\Skybox.v", "Assets\\Shaders\\Skybox.f", true);
	AssetLoader::Instance().LoadShader("TerrainNoLight", "Assets\\Shaders\\TerrainNoLight.v", "Assets\\Shaders\\TerrainNoLight.f", true);

	loading->_message = "Loading rudimentary shapes...";
	GUIManager::Instance().Render(1, 1);
	//Load basic shapes
	AssetLoader::Instance().LoadModel("Assets\\Models\\Sphere\\sphere_low.obj", true);
	AssetLoader::Instance().LoadModel("Assets\\Models\\Quad\\quad.obj", true);
	AssetLoader::Instance().LoadModel("Assets\\Models\\Cube\\cube.obj", true);
}