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


class Camera : public GameObject
{
public:


	~Camera();

	static std::vector<Camera*>& GetAllCameras() {
		return allCamerasVector;
	};

	static Camera* GetCameraByName(std::string name);

	unsigned GetCullingMask() { return cullingMask; };
	void AddLayerMask(unsigned layer) { cullingMask |= layer; };
	void RemoveLayerMask(unsigned layer){ cullingMask = cullingMask & (~layer); }
	void RemoveAllMaskLayers() { cullingMask = 0; }

	void UpdateViewMatrix();
	void Update() override;

	void SetDepth(int d) { depth = d; UpdateOrdererdCameras(); };
	int GetDepth(){ return depth; }


	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	float nearPlane;
	float farPlane;


protected:

	virtual bool OnScreenResize(Event* e) = 0;
	Transform* entityTransform;
	unsigned cullingMask;
	int depth;
	CAMERA_TYPE camerType;
	Camera(std::string name);



private:
	static std::list<Camera*> allCameras;
	static std::vector<Camera*> allCamerasVector; //Temporary;
	static void UpdateOrdererdCameras();



};







