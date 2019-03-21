#include "MeshRenderer.h"




MeshRenderer::~MeshRenderer()
{
	if (mesh->bones_id_weights_for_each_vertex.size() > 0)
		glDeleteBuffers(1, &VBO_bones);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO);
	delete mesh;

}
MeshRenderer::MeshRenderer(Mesh* m, Material mat, bool isCullable) : Renderer("MeshRenderer", mat)
{
	
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
	if (VAO == 0)
		glGenVertexArrays(1, &VAO);
	if (VBO == 0)
		glGenBuffers(1, &VBO);
	if (IBO == 0)
		glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);


	/*Bones*/
	//bones data
	if (mesh->bones_id_weights_for_each_vertex.size() > 0)
	{
		if (VBO_bones == 0)
			glGenBuffers(1, &VBO_bones);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_bones);
		glBufferData(GL_ARRAY_BUFFER, mesh->bones_id_weights_for_each_vertex.size() * sizeof(mesh->bones_id_weights_for_each_vertex[0]), &mesh->bones_id_weights_for_each_vertex[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Vertex), NULL, GL_STATIC_DRAW);

	Vertex* map = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	for (int i = 0; i < mesh->vertices.size(); i++)
	{
		map->position = mesh->vertices[i].position;
		map->normal = mesh->vertices[i].normal;
		map->UV = mesh->vertices[i].UV;
		map->color = mesh->vertices[i].color;
		map->tangent = mesh->vertices[i].tangent;
		map->binormal = mesh->vertices[i].binormal;



		map++;
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);

	//Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* mesh->indices.size(), NULL, GL_STATIC_DRAW);

	GLuint* indexPointer = (GLuint*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

	for (int i = 0; i < mesh->indices.size(); i++)
	{
		*indexPointer = mesh->indices[i];
		indexPointer++;
	}
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);


	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	//UV
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));

	//color
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	//tangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

	//bitangemnt
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, binormal));

	if (mesh->bones_id_weights_for_each_vertex.size() > 0)
	{
		//bones
		glBindBuffer(GL_ARRAY_BUFFER, VBO_bones);
		glEnableVertexAttribArray(6);
		glVertexAttribIPointer(6, 4, GL_UNSIGNED_INT, sizeof(VertexBoneData), (GLvoid*)0); // for INT Ipointer
		glEnableVertexAttribArray(7);
		glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)(16));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

Mesh* MeshRenderer::GetMesh()
{
	return mesh;
}

void MeshRenderer::Render(Camera& cam)
{
	
	SendDataToShader(cam);

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);

}