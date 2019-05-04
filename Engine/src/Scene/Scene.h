#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Core\Timer.h"
#include "..\Graphics\SkyBox.h"
#include <map>
#include <vector>
#include <list>
#include <string>

/**
* @class Scene
* @brief Generic abstract class for a scene
*
*
* @author Paolo Ferri
* @version 01
* @date 17/04/2018
*
*
* @bug No known bugs.
*/

class Scene
{
public:
	friend class SceneManager;

	/**
	* @brief		Creates the scene object
	*
	* @pre			The scene object does not exist
	* @post			The scene object is created.
	* @param n		The scene nae
	*/
	Scene(std::string n);

	/**
	* @brief		Destroy the scene object
	*
	* @pre			The scene object must exist
	* @post			The scene object is destroyed
	*/
	virtual ~Scene() {};

	/**
	* @brief		Add a gameobject to the list
	*
	* @pre			The scene object must exist, the gameobject exists
	* @post			The gameobject is added to the list for updating
	* @param go		The gameobject to be added
	*/
	void AddGameObject(GameObject* go);

	/**
	* @brief		Loads the assets needed for this scene.
	*
	* @pre			The external assets must be available.
	*/
	virtual void LoadAssets() = 0;


	/**
	* @brief		Unload the assets needed for this scene.
	*
	* @post			The assets are removed from memory.
	*/
	virtual void UnloadAssets() = 0;

	/**
	* @brief		Callback used when exiting the scene.
	*
	* @post			The scene is exited.
	*/
	virtual void QuitScene() = 0;

	/**
	* @brief		Initialize objects in the scene.
	*/
	virtual void Initialize() = 0;


	/**
	* @brief		Initialize objects in the scene.
	*/
	virtual void Start();


	/**
	* @brief		Update objects in the scene in the Logic Update Loop
	*/
	virtual void LogicUpdate() = 0;


	/**
	* @brief		Update objects in the scene in the Engine Update Loop
	*/
	virtual void EngineUpdate();

	/**
	* @brief		Update objects in the scene in the Engine Update Loop
	*				Mostly used to clear the list form dead gameobjects
	*/
	virtual void LateUpdate() ;

	/**
	* @brief		Returns whether the scene is ready
	* @return		Whether the scene has been loaded and ready
	*/
	bool GetIsReady() { return m_isReady; };

	/**
	* @brief		Returns thr skybox of the scene
	*/
	Skybox* GetSkyBox(){ return skybox; }

	/**
	* @brief		The name of the scene
	*/
	std::string name;



protected:
	/**
	* @brief		The list of gameobjects in the scene
	*/
	std::list<GameObject*> m_allGameObjects;

	/**
	* @brief		Whether the scne is ready
	*/
	bool m_isReady;

	/**
	* @brief		The skybox of the scene
	*/
	Skybox* skybox;


};