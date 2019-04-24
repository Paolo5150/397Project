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

