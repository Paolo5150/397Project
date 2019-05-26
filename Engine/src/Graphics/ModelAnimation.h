#pragma once

#include "..\GameObject\Component.h"
#include "ModelNode.h"

#include <string>
#include <map>




class Model;

/**
* @class ModelAnimation
* @brief Describe an animation for an animated model
*
* @author Paolo Ferri
* @version 01
* @date 28/04/2019
* @bug No known bugs.
*/

class ModelAnimation
{

public:
	/**
	* @brief		Constructor
	* @post			Create new animation
	*/
	ModelAnimation() {
		loop = true;
	};

	/**
	* @brief		Animation ticks
	*/
	double ticksPerSecond;

	/**
	* @brief		Animation name
	*/
	std::string animationName;

	/**
	* @brief		List of nodes for the animation
	*/
	std::map<std::string, ModelNodeAnimationInfo> allNodeAnimations;

	/**
	* @brief		Get animation info for a node
	* @param nodeName	The name of the node
	*/
	ModelNodeAnimationInfo* GetNodeAnimation(std::string nodeName);

	/**
	* @brief		Update transform for animation
	* @param animationTime	The animation time (for interpolation)
	* @param node			The node
	*/
	glm::mat4 UpdateNodeTransform(float animationTime, ModelNode* node);

	/**
	* @brief		The model being animated
	*/
	Model* model;

	/**
	* @brief		Whether the animatnion should loop
	*/
	bool loop;

	/**
	* @brief		Set animation duration
	* @param d		The animation duration
	*/
	void SetDuration(double d) { duration = d; }

	/**
	* @brief		Returns the animation duration
	* @return		The animation duration
	*/
	double GetDuration() { return duration; }

private:
	/**
	* @brief		Animation duration
	*/
	double duration;

	/**
	* @brief		Calculate the interpolated scale
	*/
	glm::vec3 calcInterpolatedScaling(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim);

	/**
	* @brief		Calculate the interpolated position
	*/
	glm::vec3 calcInterpolatedPosition(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim);

	/**
	* @brief		Calculate the interpolated rotation
	*/
	glm::quat calcInterpolatedRotation(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim);

	unsigned int findScaling(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim);
	unsigned int findPosition(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim);
	unsigned int findRotation(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim);

};



