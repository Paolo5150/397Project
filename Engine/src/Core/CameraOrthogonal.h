#include "Camera.h"

class Camera_Orthogonal : public Camera
{

	friend class Camera;
private:
	Camera_Orthogonal(float l, float r, float b, float t, float n, float f) : Camera("Camera_Orthogonal"){

		camerType = ORTHOGONAL;

		left = l;
		right = r;
		bottom = b;
		top = t;
		nearPlane = n;
		farPlane = f;

		projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);

	};

	float left;
	float right;
	float bottom;
	float top;


};