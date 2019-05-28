#include "SphereCollider.h"
#include "..\Utils\AssetLoader.h"

void SphereCollider::InitializeMeshRenderer()
{
	Material m;
	m.SetShader(AssetLoader::Instance().GetAsset<Shader>("ColorOnlyStatic"));
	m.SetColor(0, 1, 0);

	Mesh* mesh = AssetLoader::Instance().GetAsset<Model>("Sphere")->GetMeshes()[0];

	meshRenderer = new MeshRenderer(mesh, m);
}

void SphereCollider::Update()
{
	Collider::Update();
}


