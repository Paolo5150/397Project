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

/**
* @class GUIManager
* @brief Manages all GUIObjects and renders them
* This class is a facade for the ImGUI Library
* @author Paolo Ferri
* @version 01
* @date 15/03/2018
*
*
* @bug No known bugs.
*/
class GUIManager
{
public:
	/**
	* @brief		Returns the GUIManager instance
	*
	* @post			The GUIManager instance is returned
	*/
	static GUIManager& Instance();

	/**
	* @brief		The GUIManager is destroyed
	* @pre			The GUIManager must exist
	* @post			The GUIManager instance is destroyed
	*/
	~GUIManager();

	/**
	* @brief		Initialize the GUIManager, initialize the library
	* @pre			The library is installed 
	* @post			The GUIManager instance is initialized
	*/
	void Initialize();


	/**
	* @brief		Shutdown the GUIManager, close library
	* @pre			The GUIManager instance must exist
	* @post			The GUIManager is shut down
	*/
	void Shutdown();

	/**
	* @brief				Render all the GUIObjects submitted
	* @pre					The GUIObjects in the list must exist
	* @post					TThe GUIObjects in the list are rendered on the screen
	* @param forceRefresh	Whether the window will be refreshed
	* @param forceClear		Whether the window will be cleared
	*/
	void Render(bool forceRefresh = false, bool forceClear = false);

	/**
	* @brief				Add the GUIObjects to the ImGui list
	* @pre					The GUIManager instance must exist
	* @post					The GUIObjects are added to the ImGui render list
	*/
	void Refresh();

	/**
	* @brief				Add the GUIObjects to the manager list
	* @pre					The GUIManager instance must exist
	* @post					The GUIObjects are added to the manager list
	* @param gobj			The GUIObject
	* @param preserve		Whether the object will be preserved between scenes
	*/
	template <class T>
	void AddGUIObject(T* gobj, bool preserve = false);



private:

	/**
	* @brief				The list of GUIObjects not preserve
	*/
	std::map<std::string,std::list<GUIObject*>> allGUI;

	/**
	* @brief				The list of GUIObjects preserved
	*/
	std::map<std::string, std::list<GUIObject*>> allGUIPreserved;

	/**
	* @brief		Create the GUIManager instance
	*
	* @post			The GUIManager instance is created
	*/
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