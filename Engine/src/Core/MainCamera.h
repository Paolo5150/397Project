#pragma once
#include "CameraPerspective.h"
#include "Input.h"
#include "..\Components\RigidBody.h"
#include "..\Components\BoxCollider.h"
#include "..\Components\SphereCollider.h"


/**
* @class MainCamera
* @brief Specialized perspective camera used in the MainScene
*
*
* @author Paolo Ferri
* @version 01
* @date 10/04/2018
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

	/**
	* @brief		Update the camera movement according to input
	*
	* @pre			The MainCamera exists
	* @post			The MainCamera is transform is updated
	*
	*/
	void UpdateControls();

	/**
	* @brief		Method called during Logic Update
	*
	* @pre			The MainCamera exists
	* @post			The MainCamera is updated
	*
	*/
	void Update() override;

	/**
	* @brief		Set the camera speed
	*
	* @pre			The MainCamera exists
	* @post			The MainCamera speed is updated
	* @param speed  The new speed

	*/
	void SetMovementSpeed(float speed);


	/**
	* @brief		Set the camera rotation speed
	*
	* @pre			The MainCamera exists
	* @post			The MainCamera rotation speed is updated
	*
	* @param speed  The new rotation speed
	*/
	void SetRotationSpeed(float speed);

	/**
	* @brief		Get the camera speed
	*
	* @pre			The MainCamera exists
	* @post			The MainCamera speed is returned and left unchanged
	*
	*/
	float GetMovementSpeed() const;

	/**
	* @brief		Get the camera rotation speed
	*
	* @pre			The MainCamera exists
	* @post			The MainCamera rotation speed is returned and left unchanged
	*/
	float GetRotationSpeed() const;

	/**
	* @brief		Returns whether the camera is in top view mode
	*
	* @pre			The MainCamera exists
	*/
	bool IsTopView() const { return _isTopView; };

	RigidBody* rigidBody;
	BoxCollider* boxCollider;
	SphereCollider* sphereCollider;


private:
	/**
	* @brief		The camera movement speed
	*/
	float _movementSpeed;

	/**
	* @brief		The camera rotation speed
	*/
	float _rotationSpeed;

	/**
	* @brief		Whether the camera is in top view
	*/
	bool _isTopView;

	/**
	* @brief		The last position before top view
	*/
	glm::vec3 _lastPos;


};

