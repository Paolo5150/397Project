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

	// Load fonts
	
	allFonts["defaultFont"] = ImGui::GetIO().Fonts->AddFontDefault();;
	allFonts["arcadeFont"] = ImGui::GetIO().Fonts->AddFontFromFileTTF("Assets\\Fonts\\arcadeclassic\\ARCADECLASSIC.TTF", 25);;
	allFonts["invasionFont"] = ImGui::GetIO().Fonts->AddFontFromFileTTF("Assets\\Fonts\\invasion2000\\INVASION2000.TTF", 25);;


	EventDispatcher::Instance().SubscribeCallback<SceneChangedEvent>([this](Event* e){
		sceneHasChanged = 1;
		DeleteGUIObjects(0);
		return 0;
	});
	redFLashing = 0;

}



void GUIManager::Refresh()
{

	
}

void GUIManager::AddGUIObject(GUIObject* gobj, bool preserve )
{
	if (preserve)
	{
		auto it = allGUIPreserved.find(gobj->name);
		if (it == allGUIPreserved.end())
			allGUIPreserved[gobj->name] = gobj;
	}
	else
	{
		auto it = allGUI.find(gobj->name);
		if (it == allGUI.end())
			allGUI[gobj->name] = gobj;
	}

}

void GUIManager::FlashRed()
{
	redFlashTimer = 0.1f;
	SetBackgroundColor(0.8, 0.0, 0.0, 0.5);
	redFLashing = 1;

}


void GUIManager::Render(bool forceRefresh, bool forceClear)
{
	redFlashTimer = redFlashTimer < 0 ? 0 : redFlashTimer - Timer::GetDeltaS();

	if (redFlashTimer <= 0 && redFLashing == 1)
	{
		SetBackgroundColor(0.0, 0.0, 0.0, 0.0);
		redFLashing = 0;
	}

	if (forceClear)
		Core::Instance().GetGraphicsAPI().ClearColorBuffer();

	
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w));
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	
	int x, y;
	Window::Instance().GetWindowSize(x, y);
	ImGui::SetNextWindowSize(ImVec2(x, y));

	ImGui::Begin("Hello, world!",0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);

	for (auto it = allGUI.begin(); it != allGUI.end();)
	{
		if (it->second->isActive)
		it->second->RenderImGuiElement();

		// Buttons can change scene
		// When that happens, the map of gui objects is deleted!
		// So, if the scene has changed, exit the loop, otherwise keep going
		if (sceneHasChanged)
			break;
		else
			it++;
	}

	for (auto it = allGUIPreserved.begin(); it != allGUIPreserved.end();)
	{
		if (it->second->isActive)
		it->second->RenderImGuiElement();

		if (sceneHasChanged)
			break;
		else
			it++;
	}


	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::PopStyleColor();
	if (forceRefresh)
		Window::Instance().Refresh();

	sceneHasChanged = 0;

	for (auto it = buttonCallbacks.begin(); it != buttonCallbacks.end();)
	{
		(*it)();
		it = buttonCallbacks.erase(it);
		
	}
}

void GUIManager::RenderNoButtonCallbacks()
{

	Core::Instance().GetGraphicsAPI().ClearColorBuffer();
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w));
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowPos(ImVec2(0, 0));

	int x, y;
	Window::Instance().GetWindowSize(x, y);
	ImGui::SetNextWindowSize(ImVec2(x, y));

	ImGui::Begin("Hello, world!", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);

	for (auto it = allGUI.begin(); it != allGUI.end();)
	{
		if (it->second->isActive)
			it->second->RenderImGuiElement();

		// Buttons can change scene
		// When that happens, the map of gui objects is deleted!
		// So, if the scene has changed, exit the loop, otherwise keep going
		if (sceneHasChanged)
			break;
		else
			it++;
	}

	for (auto it = allGUIPreserved.begin(); it != allGUIPreserved.end();)
	{
		if (it->second->isActive)
			it->second->RenderImGuiElement();

		if (sceneHasChanged)
			break;
		else
			it++;
	}

	
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::PopStyleColor();

	Window::Instance().Refresh();

	sceneHasChanged = 0;
}

void GUIManager::SelectFont(std::string fontName)
{
	auto it = allFonts.find(fontName);

	if (it != allFonts.end())
		ImGui::PushFont(allFonts[fontName]);
	else
		ImGui::PushFont(allFonts["defaultFont"]);
}


void GUIManager::DeleteGUIObjects(bool preservedToo)
{
	
	{

		auto it = allGUI.begin();

		for (; it != allGUI.end(); it++)
		{
			delete (it->second);
			it->second = nullptr;
		}

		allGUI.clear();
	}

	{

		if (preservedToo)
		{
			auto it = allGUIPreserved.begin();

			for (; it != allGUIPreserved.end(); it++)
			{
				delete (it->second);
			}

			allGUIPreserved.clear();
		}
	}


}


void GUIManager::SetBackgroundColor(float r, float g, float b, float a)
{
	backgroundColor.x = r;
	backgroundColor.y = g;
	backgroundColor.z = b;
	backgroundColor.w = a;

}
void GUIManager::Shutdown()
{
	// Cleanup
	DeleteGUIObjects(1);
	ImGui::GetIO().Fonts->ClearFonts();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
}

