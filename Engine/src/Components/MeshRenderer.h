#pragma once
#include "Renderer.h"
#include "..\Graphics\Mesh.h"
#include "..\Graphics\ArrayBuffer.h"
#include "..\Graphics\VertexArray.h"


class MeshRenderer : public Renderer
	{

	public:
		friend class RenderingEngine;

		~MeshRenderer();
		MeshRenderer(Mesh* m, Material mat, bool isCullable = true);
		void Render(Camera& cam) override;
		Mesh& GetMesh();
		void SetMesh(Mesh* m);


		ArrayBuffer<Vertex>* vertexBuffer;
	private:
		Mesh* mesh;


		GLuint VBO_bones;

		ArrayBuffer<unsigned>* indexBuffer;	
		VertexArray* vertexArray;

		void Initialize();

	};

