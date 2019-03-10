#include "Core.h"
#include "..\Event\TimerEvents.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Logger.h"
#include "..\Event\WindowEvents.h"

void Core::Initialize()
{
	
	//Set up environment
	//Glew init MUST be called after creating the context (the window)
	if (!glfwInit())
	{
		Logger::LogError("GLFW failed to initialize");
	}
	

	Window::Initialize(); //Set context

	glewExperimental = true;
	//Initialize glew
	if (glewInit() != GLEW_OK)
	{
		Logger::LogError("GLEW failed to initialize");
	}

	//OpengGL initialization
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glClearColor(0, 0, 0, 1);


	//WINDOW
	// Set up windows after flew initialization (and after the context has been set).
	Window::Instance().SetWindowSize(1500, 800);

	//Managers initialization
	Timer::Initialize();

	//Events subscirption
	EventDispatcher::Instance().SubscribeCallback<LogicUpdateEvent>(std::bind(&Core::LogicUpdate, this, std::placeholders::_1));
	EventDispatcher::Instance().SubscribeCallback<LateUpdateEvent>(std::bind(&Core::LateUpdate, this, std::placeholders::_1));
	EventDispatcher::Instance().SubscribeCallback<RenderEvent>(std::bind(&Core::Render, this, std::placeholders::_1));
	EventDispatcher::Instance().SubscribeCallback<EngineUpdateEvent>(std::bind(&Core::EngineUpdate, this, std::placeholders::_1));

	//Close window, exit loop
	EventDispatcher::Instance().SubscribeCallback<WindowCloseEvent>([this](Event* event) -> bool{
		m_isRunning = 0;
		return 0; });

	//Get cpplication
	m_runningApplication = CreateApplication();
	m_runningApplication->AppInitialize();
	Window::Instance().SetWindowTitle(m_runningApplication->name.c_str()); //Window title -> game title

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);

	glEnd();

	Window::Instance().Refresh();
	return 0;
}