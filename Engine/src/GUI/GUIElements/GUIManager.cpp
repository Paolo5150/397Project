#include "GUIManager.h"
#include "..\..\Core\Window.h"
#include "GUIText.h"
#include "..\..\Event\ApplicationEvents.h"
#include "..\..\Core\Core.h"
#include <thread>


GUIManager& GUIManager::Instance()
{
	static GUIManager instance;
	return instance;
}

GUIManager::~GUIManager()
{}

void GUIManager::Initialize()
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(Window::Instance().window, false);
	ImGui_ImplOpenGL3_Init("#version 430");

	EventDispatcher::Instance().SubscribeCallback<SceneChangedEvent>([this](Event* e){

		DeleteGUIObjects(0);
		return 0;
	});
}



void GUIManager::Refresh()
{

	
}

void GUIManager::AddGUIObject(GUIObject* gobj, bool preserve )
{
	if (preserve)
		allGUIPreserved[gobj->name] = gobj;
	else
		allGUI[gobj->name] = gobj;

}

void GUIManager::Render(bool forceRefresh, bool forceClear)
{
	if (forceClear)
		Core::Instance().GetGraphicsAPI().ClearColorBuffer();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowBgAlpha(0.0f);

	int x, y;
	Window::Instance().GetWindowSize(x, y);
	ImGui::SetNextWindowSize(ImVec2(x, y));

	ImGui::Begin("Hello, world!",0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);


	for (auto it = allGUI.begin(); it != allGUI.end(); it++)
	{
		it->second->RenderImGuiElement();
	}

	for (auto it = allGUIPreserved.begin(); it != allGUIPreserved.end(); it++)
	{
		it->second->RenderImGuiElement();
	}

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (forceRefresh)
		Window::Instance().Refresh();
}


void GUIManager::DeleteGUIObjects(bool preservedToo)
{
	auto it = allGUI.begin();

	for (; it != allGUI.end(); it++)
	{
		delete (it->second);
	}

	allGUI.clear();
	if (preservedToo)
	{
		it = allGUIPreserved.begin();

		for (; it != allGUIPreserved.end(); it++)
		{
			delete (it->second);
		}

		allGUIPreserved.clear();

	}
}


void GUIManager::Shutdown()
{
	// Cleanup
	DeleteGUIObjects(1);


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
}

