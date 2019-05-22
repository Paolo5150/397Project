#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"
#include "..\Core\MainCamera.h"
#include "..\Components\HealthComponent.h"


class Player : public GameObject
{
public:
	Player();
	~Player();
	void Start() override;
	virtual void OnAddToScene(Scene& theScene) override;

	void Update() override;
	void UpdateControls();

	Camera* mainCamera;
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


	BoxCollider* boxCollider;
	BoxCollider* pickupCollider;

	HealthComponent* healhComponent;

	int ammoCounter;
	float shootTimer;
	GranadeLauncher* gn;

	static unsigned GetTotalPumpkinsShot(){ return totalPumpkinsShot; }
	static void ResetTotalPumpkinShots() { totalPumpkinsShot = 0; }
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

	float underwaterTimer;

	glm::vec3 _intendedDir;

	static unsigned totalPumpkinsShot;

	bool hasGun;
};