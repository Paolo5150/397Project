#include "BoxCollider.h"
#include "..\Utils\AssetLoader.h"

void BoxCollider::InitializeMeshRenderer()
{
	Material m;
	m.SetShader(AssetLoader::Instance().GetAsset<Shader>("ColorOnlyStatic"));
	m.SetColor(0, 1, 0);

	Mesh* mesh = AssetLoader::Instance().GetAsset<Model>("Cube")->GetMeshes()[0];

	meshRenderer = new MeshRenderer(mesh, m);
	collisionShape = new btBoxShape(btVector3(1,1,1));
	collisionShape->setLocalScaling(btVector3(transform.GetGlobalScale().x, transform.GetGlobalScale().y, transform.GetGlobalScale().z));

}

void BoxCollider::Update()
{

	Collider::Update();
	collisionShape->setLocalScaling(btVector3(transform.GetGlobalScale().x, transform.GetGlobalScale().y, transform.GetGlobalScale().z));
	
}


std::vector<glm::vec3> BoxCollider::GetWorldPoints()
{
	glm::vec3 p0 = transform.GetGlobalPosition() + glm::vec3(transform.GetGlobalScale().x / 2, transform.GetGlobalScale().y / 2, transform.GetGlobalScale().z / 2);
	glm::vec3 p1 = transform.GetGlobalPosition() + glm::vec3(transform.GetGlobalScale().x / 2, transform.GetGlobalScale().y / 2, -transform.GetGlobalScale().z / 2);
	glm::vec3 p2 = transform.GetGlobalPosition() + glm::vec3(transform.GetGlobalScale().x / 2, -transform.GetGlobalScale().y / 2, transform.GetGlobalScale().z / 2);
	glm::vec3 p3 = transform.GetGlobalPosition() + glm::vec3(transform.GetGlobalScale().x / 2, -transform.GetGlobalScale().y / 2, -transform.GetGlobalScale().z / 2);
	glm::vec3 p4 = transform.GetGlobalPosition() + glm::vec3(-transform.GetGlobalScale().x / 2, transform.GetGlobalScale().y / 2, transform.GetGlobalScale().z / 2);
	glm::vec3 p5 = transform.GetGlobalPosition() + glm::vec3(-transform.GetGlobalScale().x / 2, transform.GetGlobalScale().y / 2, -transform.GetGlobalScale().z / 2);
	glm::vec3 p6 = transform.GetGlobalPosition() + glm::vec3(-transform.GetGlobalScale().x / 2, -transform.GetGlobalScale().y / 2, transform.GetGlobalScale().z / 2);
	glm::vec3 p7 = transform.GetGlobalPosition() + glm::vec3(-transform.GetGlobalScale().x / 2, -transform.GetGlobalScale().y / 2, -transform.GetGlobalScale().z / 2);

	std::vector<glm::vec3> r;
	r.push_back(p0);
	r.push_back(p1);
	r.push_back(p2);
	r.push_back(p3);
	r.push_back(p4);
	r.push_back(p5);
	r.push_back(p6);
	r.push_back(p7);
	return r;


}

