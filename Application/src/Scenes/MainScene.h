#pragma once
#include "Scene/Scene.h"

class GUIImage;
class Player;
class GUIProgressBar;
/**
* @class MainScene
* @brief The application main scene
*
*
* @author Paolo Ferri
* @version 01
* @date 07/03/2018
*
*
* @bug No known bugs.
*/
class MainScene : public Scene
{
public:
	enum SCENE_STATES
	{
		PLAYING,
		GAMEOVER, 
		WIN
	};
	/**
	* @brief		Creates the MainScene object
	*
	* @pre			The MainScene object does not exist
	* @post			The MainScene object is created.
	*/
	MainScene();

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

	void Start() override;
	/**
	* @brief		Update objects in the scene.
	*/
	virtual void LogicUpdate() override;

	void DisplayMenu();
	GUIImage* manual;

	GUIImage* pumpkinAmmoImage;
	GUIText* pumpkinAmmoText;
	GUIText* endGameText;

	GUIProgressBar* healthBar;
	
	Player* player;

	void Restart();
	void UpdateUI();

	SCENE_STATES currentSceneState;

};