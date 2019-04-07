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

		auto it = allGUI[typeid(GUIText).name()].begin();
		for (; it != allGUI[typeid(GUIText).name()].end(); it++)
			delete (*it);

		allGUI[typeid(GUIText).name()].clear();

		it = allGUI[typeid(GUIImage).name()].begin();
		for (; it != allGUI[typeid(GUIImage).name()].end(); it++)
			delete (*it);

		allGUI[typeid(GUIImage).name()].clear();


		return 0;
	});
}

bool GUIManager::OnSceneChange(Event* e)
{

	return false;
}

void GUIManager::SetBackgroundColor(float r, float g, float b, float a)
{
	ImGui::SetNextWindowBgAlpha(a);
	//Need to find a way to change color...
}

void GUIManager::Refresh()
{

	//Render text
	auto it = allGUI[typeid(GUIText).name()].begin();
	for (; it != allGUI[typeid(GUIText).name()].end(); it++)
	{
		if ((*it)->isActive)
		{
			ImGui::GetWindowDrawList()->AddText(Maths::vec2ToImVec2((*it)->position),
				ImGui::GetColorU32(Maths::vec4ToImVec4(((GUIText*)(*it))->_color))
				, ((GUIText*)(*it))->_message.c_str());
		}

	}

	it = allGUIPreserved[typeid(GUIText).name()].begin();
	for (; it != allGUIPreserved[typeid(GUIText).name()].end(); it++)
	{
		if ((*it)->isActive)
		{
			ImGui::GetWindowDrawList()->AddText(Maths::vec2ToImVec2((*it)->position),
				ImGui::GetColorU32(Maths::vec4ToImVec4(((GUIText*)(*it))->_color))
				, ((GUIText*)(*it))->_message.c_str());
		}

	}

	it = allGUI[typeid(GUIImage).name()].begin();
	for (; it != allGUI[typeid(GUIImage).name()].end(); it++)
	{
		if ((*it)->isActive)
		{
			ImGui::GetWindowDrawList()->AddImage(((GUIImage*)(*it))->GetTextureID(),
				Maths::vec2ToImVec2((*it)->position), Maths::vec2ToImVec2((*it)->position + (*it)->size));
		}

	}
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

	ImGui::SetWindowFontScale(1.5);
	
	Refresh();

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (forceRefresh)
		Window::Instance().Refresh();
}


void GUIManager::Shutdown()
{
	// Cleanup
	auto it = allGUI[typeid(GUIText).name()].begin();
	for (; it != allGUI[typeid(GUIText).name()].end(); it++)
		delete (*it);

	allGUI[typeid(GUIText).name()].clear();

	it = allGUIPreserved[typeid(GUIText).name()].begin();
	for (; it != allGUIPreserved[typeid(GUIText).name()].end(); it++)
		delete (*it);

	allGUIPreserved[typeid(GUIText).name()].clear();


	it = allGUI[typeid(GUIImage).name()].begin();
	for (; it != allGUI[typeid(GUIImage).name()].end(); it++)
		delete (*it);

	allGUI[typeid(GUIImage).name()].clear();


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
}

