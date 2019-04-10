#pragma once
#include "..\..\GameObject\GameObject.h"
#include "imgui.h"
#include "..\imgui_impl_glfw.h"
#include "..\imgui_impl_opengl3.h"
#include "..\..\Core\Window.h"

class GUIObject : public InternalAsset
{
public:
	GUIObject() {
		isActive = 1;
	};
	virtual ~GUIObject(){};
	glm::vec2 position;
	glm::vec2 size;
	void Update() ;

	bool isActive;

};


