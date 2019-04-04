#pragma once
#include "CubeMap.h"
#include "Material.h"
#include "Mesh.h"
#include "..\Components\MeshRenderer.h"
#include "Layers.h"


class Skybox
{
public:
	Skybox(CubeMap* cubemap);
	~Skybox();
	Material material;

	MeshRenderer* meshRenderer;
	void Render(Camera& cam);
	int layer;
	void EngineUpdate();
	CubeMap& GetCubeMap(){ return *cubemap; }

private:
	CubeMap* cubemap;
	GameObject* g;
	void OnPreRender(Camera& cam, Shader* s);
	void OnPostRender(Camera& cam, Shader* s);


};
