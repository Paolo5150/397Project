#pragma once
#include "GridMesh.h"
#include "..\GameObject\GameObject.h"
#include "..\Components\MeshRenderer.h"

class Terrain : public GameObject
{
public:

	Terrain(int size);
	~Terrain(){};
	void ApplyHeightMap(std::string texturePaty);
	bool GenerateFaultFormation(int iterations, int minHeight, float weight, bool random);
	void OnPreRender(Camera& cam, Shader* s);
	void GetCenter(int& x, int& y,int& z);
	float GetHeightAt(int x, int z);

private:
	Material* material;
	MeshRenderer* meshRenderer;

	void NormaliseTerrain(float* heightData, int dataWidth, int dataHeight);
	void AddFilter(float* heightData, float weight, int size);
	void FilterPass(float* dataP, int increment, float weight, int size);

	int maxHeight;
	int terrainSize;
	float highMountainsRange;
	float highMountainPerc;
};
