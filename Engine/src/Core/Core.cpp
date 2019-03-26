
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

	//Managers initialization
	Timer::Initialize();
	LightManager::Instance().Initialize();

	//Get cpplication
	m_runningApplication = CreateApplication();
	Window::Instance().SetWindowTitle(m_runningApplication->name.c_str()); //Window title -> game title

	AssetLoader::Initialize(graphicsAPI);

	AssetLoader::Instance().LoadShader("ColorOnly", "Assets\\Shaders\\ColorOnly.v", "Assets\\Shaders\\ColorOnly.f");
	AssetLoader::Instance().LoadShader("DefaultStatic", "Assets\\Shaders\\DefaultStatic.v", "Assets\\Shaders\\DefaultStatic.f");

	//Load basic shapes
	AssetLoader::Instance().LoadModel("Assets\\Models\\Sphere\\sphere_low.obj");


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

	AssetLoader::Instance().Unload<Shader>(); 

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
	//m_runningApplication->AppEngineUpdate();

	return 0;
}

bool Core::LateUpdate(Event* e)
{
	m_runningApplication->AppLateUpdate();
	RenderingEngine::Instance().ClearRendererList();

	return 0;
}


bool Core::Render(Event* e)
{

	LightManager::Instance().Update();
	RenderingEngine::Instance().RenderBuffer();
	/*glEnable(GL_TEXTURE_2D);
	AssetLoader::Instance().GetAsset<Texture2D>("wood")->Bind();
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5f, -0.5f, 0.0f);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5f, -0.5f, 0.0f);

	glTexCoord2f(0.5, 1.0);
	glVertex3f(0.0f, 0.5f, 0.0f);


	glEnd();*/

	Window::Instance().Refresh();
	return 0;
}