#include "GUIManager.h"
#include "..\..\Core\Window.h"
#include "GUIText.h"

#include "..\..\Event\ApplicationEvents.h"


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

		Logger::LogError("Guimanager cleared gui");
		return 0;
	});
}

bool GUIManager::OnSceneChange(Event* e)
{
	Logger::LogError("Scene changed in gui manager");
	return false;
}

void GUIManager::SetBackgroundColor(float r, float g, float b, float a)
{
	ImGui::SetNextWindowBgAlpha(a);
	
}


void GUIManager::Render(bool forceRefresh)
{
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

	it = allGUI[typeid(GUIImage).name()].begin();
	for (; it != allGUI[typeid(GUIImage).name()].end(); it++)
	{
		if ((*it)->isActive)
		{
			ImGui::GetWindowDrawList()->AddImage(((GUIImage*)(*it))->GetTextureID(),
				Maths::vec2ToImVec2((*it)->position), Maths::vec2ToImVec2((*it)->position + (*it)->size));
		}

	}
	//ImGui::Image((ImTextureID)AssetLoader::Instance().GetAsset<Texture2D>("grass")->GetID(), ImVec2(200, 200),ImVec2(0,0),
	//					ImVec2(1,1),ImVec4(1,1,1,1),ImVec4(0,0,0,0));

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (forceRefresh)
		Window::Instance().Refresh();
}


void GUIManager::Shutdown()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	allGUI.clear();
}

