#pragma once
#include "Renderer.h"
#include "..\Graphics\Mesh.h"


class MeshRenderer : public Renderer
	{

	public:
		friend class RenderingEngine;

		~MeshRenderer();
		MeshRenderer(Mesh* m, Material mat, bool isCullable = true);
		void Render(Camera& cam) override;
		Mesh* GetMesh();
		void SetMesh(Mesh* m);


	private:
		Mesh* mesh;
		GLuint VAO;
		GLuint VBO;
		GLuint VBO_bones;

		GLuint IBO;

		void Initialize();

	};

