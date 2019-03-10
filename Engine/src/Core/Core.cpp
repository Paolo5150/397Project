#include "Core.h"
#include "..\Event\TimerEvents.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Logger.h"
#include "..\Event\WindowEvents.h"

void Core::Initialize()
{
	
	//Set up environment
	//Glew init MST be called after creating the context (the window)
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
	glClearColor(1, 0, 0, 1);


	//WINDOW
	Window::Instance().SetWindowSize(1500, 800);

	//Managers initialization
	Timer::Initialize();

	//Events subscirption
	EventDispatcher::Instance().SubscribeCallback<LogicUpdateEvent>(std::bind(&Core::LogicUpdate, this, std::placeholders::_1));
	EventDispatcher::Instance().SubscribeCallback<LateUpdateEvent>(std::bind(&Core::LateUpdate, this, std::placeholders::_1));
	EventDispatcher::Instance().SubscribeCallback<RenderEvent>(std::bind(&Core::Render, this, std::placeholders::_1));
	EventDispatcher::Instance().SubscribeCallback<EngineUpdateEvent>(std::bind(&Core::EngineUpdate, this, std::placeholders::_1));

	//Close window 
	EventDispatcher::Instance().SubscribeCallback<WindowCloseEvent>([this](Event* event) -> bool{
		m_isRunning = 0;
		return 0; });




	//Get cpplication
	m_runningApplication = CreateApplication();
	m_runningApplication->AppInitialize();

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
	//Logger::LogInfo("Logic Update",1,2,44,6,7,"random number test");
	return 0;
}

bool Core::EngineUpdate(Event* e)
{
	//Logger::LogError("Engine Update","This is how you chain stuff","pretty simple",1,3,0.5);
	return 0;
}

bool Core::LateUpdate(Event* e)
{
	return 0;
}


bool Core::Render(Event* e)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Window::Instance().Refresh();
	return 0;
}