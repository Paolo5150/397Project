#pragma once
#include "..\..\GameObject\GameObject.h"
#include "imgui.h"
#include "..\GUI\imgui_impl_glfw.h"
#include "..\GUI\imgui_impl_opengl3.h"

class GUIObject : public GameObject
{
public:
	GUIObject();
	virtual ~GUIObject();

};