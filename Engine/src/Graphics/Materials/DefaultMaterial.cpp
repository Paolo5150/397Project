#include "..\..\pch.h"
#include "DefaultMaterial.h"

DefaultMaterial::DefaultMaterial()
{
	LoadFloat("shininess", 32);
	LoadFloat("UVscale", 1.0);
}
DefaultMaterial::~DefaultMaterial()
{

}

void DefaultMaterial::LoadDiffuseTexture(Texture2D* diffuse)
{
	Loadtexture(diffuse, TextureUniform::DIFFUSE0);
}
void DefaultMaterial::LoadNormalMapTexture(Texture2D* normal)
{
	Loadtexture(normal, TextureUniform::NORMAL0);

}