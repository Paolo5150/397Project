#include "Mountains.h"

Mountains::Mountains() : GameObject("Mountains")
{
	AssetLoader::Instance().GetAsset<Model>("Mountains")->PopulateGameObject(this);

	Material mat_mountains;
	mat_mountains.SetShader(AssetLoader::Instance().GetAsset<Shader>("DefaultStatic"));
	mat_mountains.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("ground"));
	mat_mountains.LoadFloat("UVScale", 100.0f);
	mat_mountains.LoadFloat("shininess", 1000000.0f);
	ApplyMaterial(mat_mountains);

	MeshRenderer* meshRenderer = GetChild("Mountains")->GetComponentByType<MeshRenderer>("Renderer");
	meshRenderer->SetIsCullable(false);
}

Mountains::~Mountains()
{

}

