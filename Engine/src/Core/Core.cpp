
#include "Core.h"
#include "..\Event\TimerEvents.h"
#include "Logger.h"
#include "..\Event\WindowEvents.h"
#include "..\Graphics\ShaderGL.h"
#include "..\Graphics\Texture2D.h"

#include "..\Utils\AssetLoader.h"
#include "Transform.h"
#include "..\Graphics\RenderingEngine.h"
#include "..\Lighting\LightingManager.h"
#include "Input.h"
#include "imgui.h"
#include "..\GUI\imgui_impl_glfw.h"
#include "..\GUI\imgui_impl_opengl3.h"


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

	//Close window, exit loop
	EventDispatcher::Instance().SubscribeCallback<WindowCloseEvent>([this](Event* event) -> bool{
		m_isRunning = 0;
		return 0; });


	//WINDOW
	// Set up windows after flew initialization (and after the context has been set).
	Window::Instance().SetWindowSize(800, 600);
	Input::Init(false, true);

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(Window::Instance().window, false);
	ImGui_ImplOpenGL3_Init("#version 430");

	//Managers initialization
	Timer::Initialize();
	LightManager::Instance().Initialize();

	//Get cpplication
	m_runningApplication = CreateApplication();
	Window::Instance().SetWindowTitle(m_runningApplication->name.c_str()); //Window title -> game title

	AssetLoader::Initialize(graphicsAPI);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	int x, y;
	Window::Instance().GetWindowSize(x, y);
	ImGui::SetNextWindowSize(ImVec2(x, y));
	ImGui::Begin("Hello, world!", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);

	ImVec2 pos = ImGui::GetCursorScreenPos();

	ImGui::Text("Loading...");
	//ImGui::Image((ImTextureID)AssetLoader::Instance().GetAsset<Texture2D>("grass")->GetID(), ImVec2(200, 200),ImVec2(0,0),
	//					ImVec2(1,1),ImVec4(1,1,1,1),ImVec4(0,0,0,0));

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	Window::Instance().Refresh();
	//Assets loaded here are available to all scenes.
	//Load shsders
	AssetLoader::Instance().LoadShader("ColorOnly", "Assets\\Shaders\\ColorOnly.v", "Assets\\Shaders\\ColorOnly.f",true);
	AssetLoader::Instance().LoadShader("DefaultStatic", "Assets\\Shaders\\DefaultStatic.v", "Assets\\Shaders\\DefaultStatic.f", true);
	AssetLoader::Instance().LoadShader("DefaultStaticNormalMap", "Assets\\Shaders\\DefaultStaticNormalMap.v", "Assets\\Shaders\\DefaultStaticNormalMap.f", true);
	AssetLoader::Instance().LoadShader("DefaultStaticNoLight", "Assets\\Shaders\\DefaultStaticNoLight.v", "Assets\\Shaders\\DefaultStaticNoLight.f", true);
	AssetLoader::Instance().LoadShader("Terrain", "Assets\\Shaders\\Terrain.v", "Assets\\Shaders\\Terrain.f", true);
	AssetLoader::Instance().LoadShader("Water", "Assets\\Shaders\\Water.v", "Assets\\Shaders\\Water.f", true);
	AssetLoader::Instance().LoadShader("Skybox", "Assets\\Shaders\\Skybox.v", "Assets\\Shaders\\Skybox.f", true);
	AssetLoader::Instance().LoadShader("TerrainNoLight", "Assets\\Shaders\\TerrainNoLight.v", "Assets\\Shaders\\TerrainNoLight.f", true);




	//Load textures
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\water_normal.jpg", true);
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\rockNormal.jpg", true);
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\dudv.png", true);
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\grass.jpg", true);
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\ground.jpg", true);
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\rock.jpg", true);
	AssetLoader::Instance().LoadTexture("Assets\\Textures\\hm1.png", true);
	AssetLoader::Instance().LoadCubeMap("Assets\\SkyBoxes\\ClearSky", true);
	AssetLoader::Instance().LoadCubeMap("Assets\\SkyBoxes\\SunSet", true);




	//Load basic shapes
	AssetLoader::Instance().LoadModel("Assets\\Models\\Sphere\\sphere_low.obj", true);
	AssetLoader::Instance().LoadModel("Assets\\Models\\Quad\\quad.obj", true);
	AssetLoader::Instance().LoadModel("Assets\\Models\\Cube\\cube.obj", true);


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

	Logger::LogError("Engine asset clean up");
	AssetLoader::Instance().UnloadPreserved<Shader>(); 
	AssetLoader::Instance().UnloadPreserved<Texture2D>();
	AssetLoader::Instance().UnloadPreserved<Model>();



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


	

	Window::Instance().Refresh();
	return 0;
}