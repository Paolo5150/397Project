#pragma once

#include "..\GameObject\Component.h"
#include "ModelNode.h"

#include <string>
#include <map>




class Model;

class ModelAnimation
{

public:
	ModelAnimation() {
		loop = true;
	};
	~ModelAnimation() {};
	double duration;
	double ticksPerSecond;
	std::string animationName;
	std::map<std::string, ModelNodeAnimationInfo> allNodeAnimations;
	ModelNodeAnimationInfo* GetNodeAnimation(std::string nodeName);

	glm::mat4 UpdateNodeTransform(float animationTime, ModelNode* node);
	Model* model;
	bool loop;

private:
	glm::vec3 calcInterpolatedScaling(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim);
	glm::vec3 calcInterpolatedPosition(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim);
	glm::quat calcInterpolatedRotation(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim);

	unsigned int findScaling(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim);
	unsigned int findPosition(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim);
	unsigned int findRotation(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim);

};



