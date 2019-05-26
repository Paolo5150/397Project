#pragma once
#include "CameraPerspective.h"
#include "Input.h"
#include "..\Components\RigidBody.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\SphereCollider.h"
#include "..\Prefabs\GranadeLauncher.h"


/**
* @class MainCamera
* @brief Specialized perspective camera used in the MainScene
*
*
* @author Paolo Ferri
* @version 01
* @date 10/04/2019
*
*
* @bug No known bugs.
*/
class MainCamera : public CameraPerspective
{
public:

	/**
	* @brief		Create a MainCamera object
	*
	* @pre			The MainCamera does not exist
	* @post			The MainCamera is created
	*
	*/
	MainCamera();





private:
	
};

