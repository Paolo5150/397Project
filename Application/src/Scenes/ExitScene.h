#pragma once
#include "Scene/Scene.h"
#include "GUI\GUIElements\GUIImage.h"
#include "GUI\GUIElements\GUIText.h"

/**
* @class ExitScene
* @brief The application exit scene
*
* Display names and pictures of the developers.
*
* @author Paolo Ferri
* @version 01
* @date 17/04/2019
*
*
* @bug No known bugs.
*/

class ExitScene : public Scene
{
public:
	/**
	* @brief		Creates the ExitScene object
	*
	* @pre			The ExitScene object does not exist
	* @post			The ExitScene object is created.
	*/
	ExitScene();
	/**
	* @brief		Loads the assets needed for this scene.
	*
	* @pre			The external assets must be available.
	*/
	virtual void LoadAssets() override;

	/**
	* @brief		Unload the assets needed for this scene.
	*
	* @post			The assets are removed from memory.
	*/
	virtual void UnloadAssets() override;

	/**
	* @brief		Callback used when exiting the scene.
	*
	* @post			The scene is exited.
	*/
	virtual void QuitScene() override;

	/**
	* @brief		Initialize objects in the scene.
	*/
	virtual void Initialize() override;

	/**
	* @brief		Update objects in the scene.
	*/
	virtual void LogicUpdate() override;

private:



};