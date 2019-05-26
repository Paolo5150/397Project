#pragma once
#include "Model.h"
#include "ModelNode.h"
#include "ModelAnimation.h"
#include "..\GameObject\GameObject.h"




class AnimatedModel : public Model
{
public:
	friend class AssimpWrapper;
	friend class ModelAnimation;




	AnimatedModel();
	~AnimatedModel();
	static const unsigned MAX_BONES = 200;

	void GetTransformations(float animationTime, ModelAnimation* animation, std::vector<glm::mat4>& returnedTransform);
	unsigned GetTotalBones() { return totalBones; }
	GameObject* CreateGameObject() override;
	void PopulateGameObject(GameObject* go) override;
	std::vector<ModelAnimation> allAnimations;
private:

	void GetTransformations(float animationTime, ModelAnimation* animation, ModelNode* node, glm::mat4 parentTransform, std::vector<glm::mat4>& returnedTransform);
	
	ModelAnimation* currentAnimation;
	ModelNode* rootNode;
	std::map<std::string, ModelNode*> allNodes;
	std::map<std::string, ModelBone> myBoneMapping;
	unsigned totalBones = 0;

	glm::mat4 m_global_inverse_transform;
	
};

