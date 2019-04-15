#pragma once
#include "AnimatedModel.h"
#include "..\Core\Timer.h"
#include "..\GameObject\GameObject.h"
#include "..\Components\MeshRenderer.h"

#include "..\Utils\FileUtils.h"
#include "..\Utils\Maths.h"
#include "..\Core\Logger.h"
#include "..\Components\Animator.h"


AnimatedModel::AnimatedModel()
{}
AnimatedModel::~AnimatedModel()
{


}

void AnimatedModel::GetTransformations(float animationTime, ModelAnimation* animation, ModelNode* node, glm::mat4 parentTransform, std::vector<glm::mat4>& returnedTransform)
{
	std::string node_name(node->name);

	glm::mat4 currentransform = animation->UpdateNodeTransform(animationTime, node);

	glm::mat4 updatedTransform = parentTransform * currentransform;

	//Update bone transform
	auto b = myBoneMapping.find(node_name);

	if (b != myBoneMapping.end())
		returnedTransform[b->second.index] = m_global_inverse_transform * updatedTransform * b->second.offsetMatrix;


	for (int i = 0; i < node->children.size(); i++)
		GetTransformations(animationTime, animation, node->children[i], updatedTransform, returnedTransform);


}

void AnimatedModel::GetTransformations(float animationTime, ModelAnimation* animation, std::vector<glm::mat4>& returnedTransform)
{

	GetTransformations(animationTime, animation, rootNode, glm::mat4(1), returnedTransform);

}



GameObject* AnimatedModel::CreateGameObject()
{

	GameObject* e = new GameObject(name);
	Animator* anim = (Animator*)e->AddComponent(new Animator(this));

	for (int i = 0; i < allMeshes.size(); i++)
	{
		Mesh* m = new Mesh(*allMeshes[i]);

		GameObject* c = new GameObject(meshesNames[i]);

		MeshRenderer* mr = new MeshRenderer(m, allMaterials[i]); //Default material

		mr->AddPreRenderCallback(std::bind(&Animator::OnPreRender, anim, std::placeholders::_1, std::placeholders::_2));

		c->AddComponent(mr);
		e->AddChild(c);
		//anim->shaderToUpdate.insert(&allMaterials[i].GetShader());
		//anim->shaderToUpdate.insert(simplifiedMaterialGetShader());

	}
	return e;
}

