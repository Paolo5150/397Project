#include "Core.h"


void Core::Initialize()
{
	LOG_INFO("Engine initialize");
}
void Core::Run()
{
	LOG_WARNING("Engine run");

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