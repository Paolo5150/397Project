#include "Application.h"
#include "Logger.h"
#include "..\Event\EventDispatcher.h"
#include "..\Event\ApplicationEvents.h"


Application::Application()
{
	EventDispatcher::Instance().SubscribeCallback<SceneChangedEvent>([this](Event* e) {

		Logger::LogInfo("SCENE CHANGED");
		SceneChangedEvent* event = dynamic_cast<SceneChangedEvent*>(e);
		m_currentScene = event->currentScene;
		return false;
	});
}
void Application::AppEngineUpdate()
{
	Logger::LogInfo("Application engine update");
	m_currentScene->LogicUpdate();
}
void Application::AppLateUpdate()
{
	//Logger::LogInfo("Application late update");
	m_currentScene->LateUpdate();


}