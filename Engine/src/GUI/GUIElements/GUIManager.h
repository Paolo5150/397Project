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
	void AddGUIObject(T* gobj);
	void SetBackgroundColor(float r, float g, float b, float a);


private:
	bool OnSceneChange(Event* e);
	std::map<std::string,std::list<GUIObject*>> allGUI;
	GUIManager(){};
};

template <class T>
void GUIManager::AddGUIObject(T* gobj)
{
	std::string type = typeid(T).name();
	allGUI[type].push_back(gobj);
}