#pragma once
#include "Collision.h"

SphereCollider::SphereCollider() : Collider("SphereCollider"){
	Mesh* m = new Mesh(AssetLoader::Instance().GetAsset<Model>("Sphere")->GetMeshes()[0]);
	mat.SetColor(0, 1, 0);
	mat.SetShader(AssetLoader::Instance().GetAsset<Shader>("ColorOnly"));
	mr = new MeshRenderer(m, mat);

	mr->AddPreRenderCallback([this](Camera& cam, Shader* s){

		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	});
	

	mr->AddPostRenderCallback([this](Camera& cam, Shader* s){
		glEnable(GL_CULL_FACE);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	});
};

void SphereCollider::OnAttach(GameObject* go)
{
	mr->SetParent(go);
	trans.parent = &go->transform;
	mr->transform = &trans;
}



bool SphereCollider::checkCollision(SphereCollider other){
	if (!this->_isActive || !other.GetActive()) return 0;

	float dist = glm::length(other.trans.GetGlobalPosition() - trans.GetGlobalPosition());

	float sumRad = trans.GetGlobalScale().x / 2 + other.trans.GetGlobalScale().x / 2;

	if (dist < sumRad)
		return true;
	
	return false;


}

void SphereCollider::EngineUpdate()
{ 
	if (_isActive)
	{
	
	trans.Update();
	mr->EngineUpdate();
	}

}