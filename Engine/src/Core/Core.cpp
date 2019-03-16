#include "Core.h"
#include "..\Event\TimerEvents.h"
#include "Logger.h"
#include "..\Event\WindowEvents.h"
#include "..\Graphics\ShaderGL.h"
#include "..\Graphics\Texture2D.h"

#include "..\Utils\AssetLoader.h"

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
	Window::Instance().SetWindowSize(1500, 800);

	//Managers initialization
	Timer::Initialize();

	//Get cpplication
	m_runningApplication = CreateApplication();
	m_runningApplication->AppInitialize();
	Window::Instance().SetWindowTitle(m_runningApplication->name.c_str()); //Window title -> game title

	AssetLoader::Initialize(graphicsAPI);

	AssetLoader::Instance().LoadShader("ColorOnly", "Assets\\Shaders\\coloronly.v", "Assets\\Shaders\\coloronly.f");
	Texture2D* t = AssetLoader::Instance().LoadTexture("wood", "Assets\\Textures\\wood.jpg");
	Logger::LogInfo("Text ", t->name);


	//Start update loop
	m_isRunning = true;
}
void Core::Run()
{

	while (m_isRunning)
	{
		// Just update the timer
		// The timer will send out events for update, render and so on
		Timer::Update();
		Window::Instance().UpdateEvents();		
	}
}
void Core::Shutdown()
{

	AssetLoader::Instance().Unload<Shader>();
	AssetLoader::Instance().Unload<Texture2D>();

	graphicsAPI->Shutdown();
	m_runningApplication->AppShutdown();
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
	Logger::LogInfo("Logic Update",1,2,44,6,7,"random number test");
	return 0;
}

GraphicsAPI& Core::GetGraphicsAPI()
{
	return *graphicsAPI;
}

bool Core::EngineUpdate(Event* e)
{

	return 0;
}

bool Core::LateUpdate(Event* e)
{
	return 0;
}


bool Core::Render(Event* e)
{
	graphicsAPI->ClearColorBuffer();
	graphicsAPI->ClearDepthBuffer();

	glEnable(GL_TEXTURE_2D);
	AssetLoader::Instance().GetAsset<Texture2D>("wood")->Bind();
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5f, -0.5f, 0.0f);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5f, -0.5f, 0.0f);

	glTexCoord2f(0.5, 1.0);
	glVertex3f(0.0f, 0.5f, 0.0f);


	glEnd();

	Window::Instance().Refresh();
	return 0;
}