#pragma once
#include "GridMesh.h"
#include "..\GameObject\GameObject.h"
#include "..\Components\MeshRenderer.h"

class Terrain : public GameObject
{
public:

	Terrain(unsigned size);
	~Terrain(){};
	void ApplyHeightMap(std::string texturePaty, float maxHeight);
	void GenerateFaultFormation();

	void OnPreRender(Camera& cam, Shader* s);

private:
	Material* material;
	MeshRenderer* meshRenderer;

	unsigned size;
};
