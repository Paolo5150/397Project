#pragma once
#include "Model.h"
#include "ModelNode.h"
#include "ModelAnimation.h"
#include "..\GameObject\GameObject.h"



/**
* @class AnimatedModel
* @brief Describe a 3D animated model
*
* @author Paolo Ferri
* @version 01
* @date 15/05/2019
*
*
* @bug No known bugs.
*/
class AnimatedModel : public Model
{
public:
	friend class AssimpWrapper;
	friend class ModelAnimation;

	/**
	* @brief		Creates the model object
	* @post			The model is created
	*/
	AnimatedModel();

	/**
	* @brief		Destroy the AnimatedModel object
	* @pre			The AnimatedModel object exist
	* @post			The AnimatedModel is destroyed
	*/
	~AnimatedModel();

	/**
	* @brief		Maximum number of bones allowed
	*/
	static const unsigned MAX_BONES = 200;

	/**
	* @brief					Returns all the transform matrices of all bone nodes
	* @pre						The AnimatedModel object exist
	* @param animationTime		Increasing animation time
	* @param animation			The animation being played
	* @param returnedTransform	The returned list of transforms
	*/
	void GetTransformations(float animationTime, ModelAnimation* animation, std::vector<glm::mat4>& returnedTransform);

	/**
	* @brief					Returns the total number of bones
	*/
	unsigned GetTotalBones() { return totalBones; }


	/**
	* @brief					Returns a Gameobject based on the current model with necessary components
	*/
	GameObject* CreateGameObject() override;

	/**
	* @brief					Pupulate a Gameobject based on the current model with necessary components
	*/
	void PopulateGameObject(GameObject* go) override;

	/**
	* @brief					All the animation of the model
	*/
	std::vector<ModelAnimation> allAnimations;
private:
	/**
	* @brief					Recursive methods for returning transforms
	*/
	void GetTransformations(float animationTime, ModelAnimation* animation, ModelNode* node, glm::mat4 parentTransform, std::vector<glm::mat4>& returnedTransform);
	
	/**
	* @brief					The current animation
	*/
	ModelAnimation* currentAnimation;

	/**
	* @brief					The root node
	*/
	ModelNode* rootNode;

	/**
	* @brief					All model  nodes
	*/
	std::map<std::string, ModelNode*> allNodes;

	/**
	* @brief					Map of bones by name
	*/
	std::map<std::string, ModelBone> myBoneMapping;

	/**
	* @brief					Total bones
	*/
	unsigned totalBones = 0;

	glm::mat4 m_global_inverse_transform;
	
};

