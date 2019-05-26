#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"
#include "..\Components\BoxCollider.h"
#include "..\Lighting\PointLight.h"

/**
* @class GranadeLauncher
* @brief Premade gameobject for the GranadeLauncher object
*
*
* @author Paolo Ferri
* @version 01
* @date 11/05/2018
*
*
* @bug No known bugs.
*/
class GranadeLauncher : public GameObject
{
public:
	/**
	* @brief		Constructor
	* @pre			The GranadeLauncher object does not exist
	* @post			The GranadeLauncher object is created
	*/
	GranadeLauncher();

	/**
	* @brief		Destructor
	* @pre			The GranadeLauncher object must exist
	* @post			The GranadeLauncher object is destroyed
	*/
	~GranadeLauncher();

	/**
	* @brief		Initialize barrel
	* @pre			The GranadeLauncher object must exist
	* @post			The GranadeLauncher object is initialized, colliders are added
	*/
	void Start() override;

	/**
	* @brief		Overridden callback for update method
	* @pre			The GranadeLauncher object must exist
	*/
	void Update() override;

	/**
	* @return		The gun's collider
	*/
	BoxCollider* GetCollider() { return boxCollider; }

	/**
	* @brief		Whether the gun should spin
	*/
	bool spin;

	/**
	* @brief		Point light used to hightlight the gun on the terrain
	*/
	PointLight* pointLight;
private:
	/**
	* @brief		The gun collider
	*/
	BoxCollider* boxCollider;



};