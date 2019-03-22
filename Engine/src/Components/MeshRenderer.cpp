#include "MeshRenderer.h"




MeshRenderer::~MeshRenderer()
{
	if (mesh->bones_id_weights_for_each_vertex.size() > 0)
		glDeleteBuffers(1, &VBO_bones);


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



	vertexBuffer.AddData(mesh->vertices);
	indexBuffer.AddData(mesh->indices);



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