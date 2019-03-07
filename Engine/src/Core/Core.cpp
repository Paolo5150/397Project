#include "Core.h"
#include "..\Event\TimerEvents.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void Core::Initialize()
{



	//Set up environment
	//Glew init MST be called after creating the context (the window)
	glfwInit();

	glewExperimental = true;
	//Initialize glew
	glewInit();


	//OpengGL initialization
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);



	//Standard shapes



	//Managers initialization
	Timer::Initialize();

	//Events subscirption
	EventDispatcher::Instance().SubscribeCallback<LogicUpdateEvent>(std::bind(&Core::LogicUpdate, this, std::placeholders::_1));
	EventDispatcher::Instance().SubscribeCallback<LateUpdateEvent>(std::bind(&Core::LateUpdate, this, std::placeholders::_1));
	EventDispatcher::Instance().SubscribeCallback<RenderEvent>(std::bind(&Core::Render, this, std::placeholders::_1));
	EventDispatcher::Instance().SubscribeCallback<EngineUpdateEvent>(std::bind(&Core::EngineUpdate, this, std::placeholders::_1));



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
	std::cout << "Update\n";
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

	return 0;
}