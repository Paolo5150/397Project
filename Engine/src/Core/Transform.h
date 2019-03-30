#pragma once
#include "..\Utils\Maths.h"
#include <sstream>

class Transform
{
public:



	Transform* parent;

	Transform();

	glm::vec3& GetPosition();
	glm::vec3& GetScale();
	glm::vec3& GetRotation();

	glm::vec3& GetGlobalPosition();
	glm::vec3& GetGlobalScale();
	glm::mat4& GetGlobalRotation();

	glm::vec3& GetLocalFront() { return localFront; };
	glm::vec3& GetLocalRight() { return localRight; };
	glm::vec3& GetLocalUp() { return localUp; };

	glm::mat4& GetMatrix();

	void RotateBy(float angle, glm::vec3 acis);
	void RotateBy(float angle, int x, int y, int z);



	void SetPosition(glm::vec3 r);
	void SetScale(glm::vec3 r);
	void LookAt(glm::vec3 target);

	void SetRotation(float x, float y, float z);
	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void LookAt(float x, float y, float z);
	void Translate(float x, float y, float z);

	void Update();



	std::string ToString();
	std::string VectorsToString();

private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	glm::quat rotationQuat;

	glm::vec3 localFront;
	glm::vec3 localRight;
	glm::vec3 localUp;

	glm::mat4 modelMatrix;

	glm::vec3 globalPosition;
	glm::vec3 globalScale;
	glm::mat4 globalRotationMatrix;
	glm::mat4 rotationMatrix;


	glm::mat4 GetTranslateMatrix();
	glm::mat4 GetScaleMatrix();
	glm::mat4 GetRotationMatrix();


	void UpdateVectors();





};