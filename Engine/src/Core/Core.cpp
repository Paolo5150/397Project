#include "Core.h"


void Core::Initialize()
{
	LOG_INFO("Engine initialize");

	//Set up environment
	//Glfw init MST be called after creating the context (the window)
	if (!glfwInit())
		LOG_ERROR("Failed to initialize GLFW");

	//Create Window



	//glewExperimental = true;
	glewExperimental = true; //Apparently this is necessary to use shaders
	//Initialize glew
	if (!glewInit())
		LOG_ERROR("Failed to initialize GLEW");

	//OpengGL initialization
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);


	//Standard shapes



	//Managers initialization
	Timer::Initialize();

	//Events subscirption
	//EventDispatcher::Instance().SubscribeCallback<LogicUpdateEvent>(std::bind(&Core::Update, this, std::placeholders::_1));


	//Get cpplication
	m_runningApplication = CreateApplication();
	m_runningApplication->AppInitialize();

	//Start update loop
	m_isRunning = true;
}
void Core::Run()
{
	LOG_WARNING("Engine run");
	/*while (m_isRunning)
	{
		// Just update the timer
		// The timer will send out events for update, render and so on
		Timer::Update();
	}*/
}
void Core::Shutdown()
{
	LOG_ERROR("Engine shutdown");
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

bool Core::Update(Event* e)
{
	LOG_INFO("Update received");
	return 0;
}