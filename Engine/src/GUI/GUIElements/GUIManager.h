#pragma once

#include "imgui.h"
#include "..\imgui_impl_glfw.h"
#include "..\imgui_impl_opengl3.h"
#include "GUIText.h"
#include "GUIImage.h"

#include <list>
#include <map>
#include "..\..\Event\EventDispatcher.h"

class GUIObject;

class GUIManager
{
public:
	static GUIManager& Instance();
	~GUIManager();

	void Initialize();
	void Shutdown();
	void Render(bool forceRefresh = false, bool forceClear = false);
	void Refresh();

	template <class T>
	void AddGUIObject(T* gobj, bool preserve = false);
	void SetBackgroundColor(float r, float g, float b, float a);


private:
	bool OnSceneChange(Event* e);
	std::map<std::string,std::list<GUIObject*>> allGUI;
	std::map<std::string, std::list<GUIObject*>> allGUIPreserved;

	GUIManager(){};
};

template <class T>
void GUIManager::AddGUIObject(T* gobj, bool preserve)
{
	std::string type = typeid(T).name();
	if (!preserve)
		allGUI[type].push_back(gobj);
	else
		allGUIPreserved[type].push_back(gobj);

}