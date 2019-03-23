#pragma once

#include "..\Material.h"

class DefaultMaterial : public Material
{
public:
	DefaultMaterial();
	~DefaultMaterial();
	void LoadDiffuseTexture(Texture2D* diffuse);
	void LoadNormalMapTexture(Texture2D* normal);

};