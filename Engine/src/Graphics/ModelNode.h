#pragma once
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <string>
#include <vector>

/**
* @class ModelNode
* @brief Describe a joint in an animated model
* CURRENTLY NOT IMPLEMENTED
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2018
*
*
* @bug No known bugs.
*/
class ModelNode
{

public:
	std::string name;
	glm::mat4 transform;
	std::vector<ModelNode*> children;
};

/*
class TranslateKey
{
public:
	TranslateKey(double t, glm::vec3 v) : time(t), value(v) {}
	double time;
	glm::vec3 value;
};

class ScaleKey
{
public:
	ScaleKey(double t, glm::vec3 v) : time(t), value(v) {}
	double time;
	glm::vec3 value;
};

class RotationKey
{
public:
	RotationKey(double t, glm::quat v) : time(t), value(v) {}
	double time;
	glm::quat value;
};


class ModelNodeAnimationInfo
{

public:
	ModelNode* actualNode;
	std::vector<TranslateKey> translateKeys;
	std::vector<ScaleKey> scaleKeys;
	std::vector<RotationKey> rotationKey;
};


class ModelBone {

public:
	glm::mat4 offsetMatrix;

	unsigned int index;
};

*/