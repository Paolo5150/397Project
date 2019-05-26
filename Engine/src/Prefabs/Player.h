#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"
#include "..\Core\MainCamera.h"
#include "..\Components\HealthComponent.h"

class Companion;

/**
* @class Player
* @brief Premade gameobject for the player object
*
*
* @author Paolo Ferri
* @version 01
* @date 15/05/2019
*
*
* @bug No known bugs.
*/
class Player : public GameObject
{
public:
	/**
	* @brief		Constructor
	* @pre			The player object does not exist
	* @post			The player object is created
	*/
	Player();

	/**
	* @brief		Destructor
	* @pre			The player object must exist
	* @post			The player object is destroyed
	*/
	~Player();

	/**
	* @brief		Initialize player
	* @pre			The player object must exist
	* @post			The player object is initialized, colliders are added
	*/
	void Start() override;

	/**
	* @brief		Overridden callback when the player is added to the scene
	* @pre			The player object must exist
	*/
	virtual void OnAddToScene(Scene& theScene) override;

	/**
	* @brief		Overridden callback for update method
	* @pre			The player object must exist
	*/
	void Update() override;

	/**
	* @brief		Read keyboards input to move the player
	* @pre			The player object must exist
	* @post			The player moves with keyboard/mouse
	*/
	void UpdateControls();

	/**
	* @brief		Reference to main camera object
	*/
	Camera* mainCamera;

	/**
	* @brief		Overridden callback for late update method
	* @pre			The player object must exist
	*/
	void LateUpdate();

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
	* @brief		Box collider used for collisions
	*/
	BoxCollider* boxCollider;

	/**
	* @brief		Box collider used for collisions
	*/
	BoxCollider* pickupCollider;

	/**
	* @brief		Health component, keeps track of player health
	*/
	HealthComponent* healhComponent;

	/**
	* @return			The ammo available
	*/
	int GetAmmos() { return ammoCounter; }

	/**
	* @brief		returns total number of pumpkins shot
	* @return		The total number of pumpkins shot
	*/
	static unsigned GetTotalPumpkinsShot(){ return totalPumpkinsShot; }

	/**
	* @brief		Reset total number of pumpkins shot
	*/
	static void ResetTotalPumpkinShots() { totalPumpkinsShot = 0; }
private:
	/**
	* @brief		The gun model
	*/
	GranadeLauncher* gn;

	/**
	* @brief		Keeps track of shoot rate
	*/
	float shootTimer;

	/**
	* @brief		Number of ammos available
	*/
	int ammoCounter;
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

	/**
	* @brief		Tracks the time the player spent underwater
	*/
	float underwaterTimer;

	/**
	* @brief		Intended direction in world space according to input
	*/
	glm::vec3 _intendedDir;

	/**
	* @brief		Total number of pumpkins shot
	*/
	static unsigned totalPumpkinsShot;

	/**
	* @brief		Whether the gun has been picked up
	*/
	bool hasGun;

	Companion* companion;
};