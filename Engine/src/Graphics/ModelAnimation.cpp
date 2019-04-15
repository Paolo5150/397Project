#include "ModelAnimation.h"
#include "Model.h"
#include "..\Utils\Maths.h"



ModelNodeAnimationInfo* ModelAnimation::GetNodeAnimation(std::string nodeName)
{
	auto it = allNodeAnimations.find(nodeName);

	if (it != allNodeAnimations.end())
		return &it->second;
	else return NULL;

}

glm::mat4 ModelAnimation::UpdateNodeTransform(float animationtime, ModelNode* node)
{
	ModelNodeAnimationInfo* animationInfoForNode = GetNodeAnimation(node->name);


	//Update current transform with interpolation from animation
	if (animationInfoForNode)
	{

		glm::vec3 scaling = calcInterpolatedScaling(animationtime, animationInfoForNode);
		glm::mat4 scale;
		scale = glm::scale(scale, scaling);

		glm::vec3 translation = calcInterpolatedPosition(animationtime, animationInfoForNode);
		glm::mat4 trans;
		trans = glm::translate(trans, translation);

		glm::quat rotation = calcInterpolatedRotation(animationtime, animationInfoForNode);
		glm::mat4 rot = glm::toMat4(rotation);


		return trans * rot * scale;;

	}
	else
	{
		return	node->transform;
	}


}

unsigned int ModelAnimation::findPosition(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim)
{

	for (unsigned i = 0; i < p_node_anim->translateKeys.size() - 1; i++)
	{
		if (p_animation_time < (float)p_node_anim->translateKeys[i + 1].time)
		{
			return i;
		}
	}


	return 0;
}

unsigned int ModelAnimation::findRotation(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim)
{

	for (unsigned i = 0; i < p_node_anim->rotationKey.size() - 1; i++)
	{
		if (p_animation_time < (float)p_node_anim->rotationKey[i + 1].time)
		{
			return i;
		}
	}


	return 0;
}


unsigned int ModelAnimation::findScaling(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim)
{

	for (unsigned i = 0; i < p_node_anim->scaleKeys.size() - 1; i++)
	{
		if (p_animation_time < (float)p_node_anim->scaleKeys[i + 1].time)
		{
			return i;
		}
	}
	assert(0);

	return 0;
}


glm::vec3 ModelAnimation::calcInterpolatedScaling(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim)
{
	if (p_node_anim->scaleKeys.size() == 1)
	{
		return p_node_anim->scaleKeys[0].value;
	}


	unsigned scaling_index = findScaling(p_animation_time, p_node_anim);
	unsigned next_scaling_index = scaling_index + 1;


	float delta_time = (float)(p_node_anim->scaleKeys[next_scaling_index].time - p_node_anim->scaleKeys[scaling_index].time);

	float  factor = (p_animation_time - (float)p_node_anim->scaleKeys[scaling_index].time) / delta_time;

	glm::vec3 start = p_node_anim->scaleKeys[scaling_index].value;
	glm::vec3 end = p_node_anim->scaleKeys[next_scaling_index].value;
	glm::vec3 delta = end - start;

	return start + factor * delta;
}

glm::vec3 ModelAnimation::calcInterpolatedPosition(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim)
{
	if (p_node_anim->translateKeys.size() == 1) 
	{
		return p_node_anim->translateKeys[0].value;
	}

	unsigned position_index = findPosition(p_animation_time, p_node_anim);
	unsigned next_position_index = position_index + 1;


	float delta_time = (float)(p_node_anim->translateKeys[next_position_index].time - p_node_anim->translateKeys[position_index].time);

	float factor = (p_animation_time - (float)p_node_anim->translateKeys[position_index].time) / delta_time;

	glm::vec3 start = p_node_anim->translateKeys[position_index].value;
	glm::vec3 end = p_node_anim->translateKeys[next_position_index].value;
	glm::vec3 delta = end - start;

	return start + factor * delta;
}

glm::quat ModelAnimation::calcInterpolatedRotation(float p_animation_time, const ModelNodeAnimationInfo* p_node_anim)
{

	if (p_node_anim->rotationKey.size() == 1)
	{
		return p_node_anim->rotationKey[0].value;
	}

	unsigned rotation_index = findRotation(p_animation_time, p_node_anim);
	unsigned next_rotation_index = rotation_index + 1;


	float delta_time = (float)(p_node_anim->rotationKey[next_rotation_index].time - p_node_anim->rotationKey[rotation_index].time);

	float factor = (p_animation_time - (float)p_node_anim->rotationKey[rotation_index].time) / delta_time;


	glm::quat start_quat = p_node_anim->rotationKey[rotation_index].value;
	glm::quat end_quat = p_node_anim->rotationKey[next_rotation_index].value;


	return Maths::nlerp(start_quat, end_quat, factor);
}