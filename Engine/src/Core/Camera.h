#pragma once
#include "..\Event\EventDispatcher.h"
#include "..\Event\WindowEvents.h"
#include "..\GameObject\GameObject.h"
#include "..\Core\Logger.h"
#include "..\Graphics\Layers.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <map>
#include <list>
#include <string>


enum CAMERA_TYPE
{
	PERSPECTIVE,
	ORTHOGONAL
};

/**
* @class Camera
* @brief Generic class that defines a virtual camera
*
*
* @author Paolo Ferri
* @version 01
* @date 21/03/2018
*
*
* @bug No known bugs.
*/

class Camera : public GameObject
{
public:
	/**
	* @brief Destroy the camera object
	*
	* @pre The camera object exists
	* @post The camera object is destroyed
	*/
	~Camera();

	/**
	* @brief Get the list of created cameras
	*
	* @pre The list eists
	* @post The list is returned
	*/
	static std::vector<Camera*>& GetAllCameras() {
		return allCamerasVector;
	};

	/**
	* @brief Get a specific camera by name
	*
	* @post If available, the camera first camera with matching name is returned. Nullptr is returned if not found
	*/
	static Camera* GetCameraByName(std::string name);

	/**
	* @brief Get the culling layers of the camera
	*/
	unsigned GetCullingMask() { return cullingMask; };

	/**
	* @brief Remove a layer from the culling mask
	*/
	void AddLayerMask(unsigned layer) { cullingMask |= layer; };

	/**
	* @brief Add a layer to the culling mask
	*/
	void RemoveLayerMask(unsigned layer){ cullingMask = cullingMask & (~layer); }

	/**
	* @brief Add all layers from the culling mask
	*/
	void RemoveAllMaskLayers() { cullingMask = 0; }

	/**
	* @brief Update the view matrix of the camera based on position and rotation of the object.
	*
	* @pre The view matrix exists
	* @post The view matrix is updated
	*/
	void UpdateViewMatrix();

	/**
	* @brief Update the object
	*
	* @pre The object exists and added to a scene
	* @post The object is updated
	*/
	void Update() override;

	/**
	* @brief Set the camera depth
	*
	* @param d The new camera depth
	*/
	void SetDepth(int d) { depth = d; UpdateOrdererdCameras(); };

	/**
	* @brief Set the camera depth
	*
	* @param d The new camera depth
	*/
	int GetDepth(){ return depth; }

	/**
	* @brief Return the view matrix of the camera
	*/
	glm::mat4& GetViewMatrix() { return viewMatrix; }

	/**
	* @brief Return the projection matrix of the camera
	*/
	glm::mat4& GetProjectionMatrix() { return projectionMatrix; }

protected:

	virtual bool OnScreenResize(Event* e) = 0;
	Transform* entityTransform;
	unsigned cullingMask;
	int depth;
	CAMERA_TYPE camerType;
	Camera(std::string name);
	std::string resizeEventToken;


	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	float nearPlane;
	float farPlane;




private:
	static std::list<Camera*> allCameras;
	static std::vector<Camera*> allCamerasVector; //Temporary;
	static void UpdateOrdererdCameras();



};







