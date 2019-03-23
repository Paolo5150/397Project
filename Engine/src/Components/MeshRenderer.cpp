#include "MeshRenderer.h"
#include "..\Core\Core.h"



MeshRenderer::~MeshRenderer()
{
	if (mesh->bones_id_weights_for_each_vertex.size() > 0)
		glDeleteBuffers(1, &VBO_bones);

	delete vertexArray;
	delete vertexBuffer;
	delete indexBuffer;

	delete mesh;

}
MeshRenderer::MeshRenderer(Mesh* m, Material mat, bool isCullable) : Renderer("MeshRenderer", mat)
{
	vertexArray = Core::Instance().GetGraphicsAPI().CreateVertexArray();
	vertexBuffer = Core::Instance().GetGraphicsAPI().CreateVertexBuffer();
	indexBuffer = Core::Instance().GetGraphicsAPI().CreateIndexBuffer();

	
	this->isCullable = isCullable;
	SetMesh(m);
}

void MeshRenderer::SetMesh(Mesh* m)
{
	if (this->mesh != NULL)
		delete mesh;

	mesh = m;
	Initialize();
}


void MeshRenderer::Initialize()
{
	
	vertexArray->Bind();

	/*Bones*/
	//bones data
	/*if (mesh->bones_id_weights_for_each_vertex.size() > 0)
	{
		if (VBO_bones == 0)
			glGenBuffers(1, &VBO_bones);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_bones);
		glBufferData(GL_ARRAY_BUFFER, mesh->bones_id_weights_for_each_vertex.size() * sizeof(mesh->bones_id_weights_for_each_vertex[0]), &mesh->bones_id_weights_for_each_vertex[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}*/

	vertexBuffer->AddData(mesh->vertices);
	indexBuffer->AddData(mesh->indices);

	//Position
	vertexArray->AddLayoutf(0, 3, false, sizeof(Vertex), 0);

	//normal
	vertexArray->AddLayoutf(1, 3, false, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	//UV
	vertexArray->AddLayoutf(2, 2, false, sizeof(Vertex), (void*)offsetof(Vertex, UV));

	//color
	vertexArray->AddLayoutf(3, 3, false, sizeof(Vertex), (void*)offsetof(Vertex, color));

	//tangent
	vertexArray->AddLayoutf(4, 3, false, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

	//bitangemnt
	vertexArray->AddLayoutf(5, 3, false, sizeof(Vertex), (void*)offsetof(Vertex, binormal));

	/*if (mesh->bones_id_weights_for_each_vertex.size() > 0)
	{
		//bones
		glBindBuffer(GL_ARRAY_BUFFER, VBO_bones);
		glEnableVertexAttribArray(6);
		glVertexAttribIPointer(6, 4, GL_UNSIGNED_INT, sizeof(VertexBoneData), (GLvoid*)0); // for INT Ipointer
		glEnableVertexAttribArray(7);
		glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)(16));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}*/

	vertexArray->Unbind();
}

Mesh* MeshRenderer::GetMesh()
{
	return mesh;
}

void MeshRenderer::Render(Camera& cam)
{	
	SendDataToShader(cam);
	vertexArray->RenderArrayTriangles(mesh->indices.size());
}