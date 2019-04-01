#include "Terrain.h"
#include "..\Utils\AssetLoader.h"
#include "..\Graphics\Layers.h"


Terrain::Terrain(unsigned size) : GameObject("Terrain")
{
	this->size = size;

	Material material;
	material.SetShader(AssetLoader::Instance().GetAsset<Shader>("Terrain"));
	material.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("grass"));
	material.LoadFloat("UVscale", 8.0f);

	SetLayer(0);
	SetLayer(Layers::TERRAIN);

	Mesh*m = new GridMesh(size, size);
	meshRenderer = new MeshRenderer(m, material);
	meshRenderer->AddPreRenderCallback(std::bind(&Terrain::OnPreRender, this, std::placeholders::_1, std::placeholders::_2));
	meshRenderer->isCullable = false;
	
	this->AddComponent(meshRenderer);
}

void Terrain::OnPreRender(Camera& cam, Shader* s)
{

}
