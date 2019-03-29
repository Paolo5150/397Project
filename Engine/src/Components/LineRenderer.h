#pragma once
#include "Renderer.h"
#include "..\Graphics\Mesh.h"
#include "..\Graphics\ArrayBuffer.h"
#include "..\Graphics\VertexArray.h"


class LineRenderer : public Renderer
{

public:
	friend class RenderingEngine;

	~LineRenderer();
	LineRenderer(std::vector<Vertex> verts);
	void Render(Camera& cam) override;
	void OnPreRender(Camera& cam, Shader* currentShader = nullptr) override;
	void SetVertices(std::vector<Vertex> verts);
	void SetColor(float r, float g, float b);

private:

	ArrayBuffer<Vertex>* vertexBuffer;
	VertexArray* vertexArray;
	std::vector<Vertex> vertices;

	void Initialize();

};

