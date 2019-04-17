#pragma once
#include "..\..\GameObject\GameObject.h"
#include "imgui.h"
#include "..\imgui_impl_glfw.h"
#include "..\imgui_impl_opengl3.h"
#include "..\..\Core\Window.h"

/**
* @class GUIObject
* @brief Parent abstract class to all GUI objects

* @author Paolo Ferri
* @version 01
* @date 15/03/2018
*
*
* @bug No known bugs.
*/
class GUIObject : public InternalAsset
{
public:
	/**
	* @brief		Creates a GUIObject
	*
	* @post			The GUIObject object is created
	*/
	GUIObject() {
		isActive = 1;
	};

	/**
	* @brief		Destroy a GUIObject
	*
	* @pre			The GUIObject must exist
	* @post			The GUIObject object is destroyed
	*/
	virtual ~GUIObject(){};

	/**
	* @brief		The position on the screen
	*/
	glm::vec2 position;

	/**
	* @brief		The size of the element
	*/
	glm::vec2 size;

	/**
	* @brief		Whether the GUIObject is active or not
	*/
	bool isActive;

};


