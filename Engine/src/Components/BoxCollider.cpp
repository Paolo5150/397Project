#include "BoxCollider.h"
#include "..\Utils\AssetLoader.h"

void BoxCollider::InitializeMeshRenderer()
{
	Material m;
	m.SetShader(AssetLoader::Instance().GetAsset<Shader>("ColorOnlyStatic"));
	m.SetColor(0, 1, 0);

	Mesh* mesh = AssetLoader::Instance().GetAsset<Model>("Cube")->GetMeshes()[0];

	meshRenderer = new MeshRenderer(mesh, m);
	transform.SetScale(5, 5, 5);


	collisionShape = new btBoxShape(btVector3(transform.GetGlobalScale().x, transform.GetGlobalScale().y, transform.GetGlobalScale().z));
	collisionShape->calculateLocalInertia(1, btVector3(1.0f, 1.0f, 1.0f));
}
