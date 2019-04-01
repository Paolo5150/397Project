#pragma once
#include "GridMesh.h"
#include "..\GameObject\GameObject.h"
#include "..\Components\MeshRenderer.h"

class Terrain : public GameObject
{
public:

	Terrain(int size);
	~Terrain(){};
	void ApplyHeightMap(std::string texturePaty, float maxHeight);
	bool GenerateFaultFormation(int iterations, int minHeight, int maxHeight, float weight, bool random);
	void OnPreRender(Camera& cam, Shader* s);

private:
	Material* material;
	MeshRenderer* meshRenderer;

	void NormaliseTerrain(float* heightData, int dataWidth, int dataHeight);
	void AddFilter(float* heightData, float weight, int size);
	void FilterPass(float* dataP, int increment, float weight, int size);

	int terrainSize;
};
