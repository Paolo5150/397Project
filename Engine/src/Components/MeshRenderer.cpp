#include "MeshRenderer.h"
#include "..\Core\Core.h"



MeshRenderer::~MeshRenderer()
{
	//if (mesh->bones_id_weights_for_each_vertex.size() > 0)
	//	glDeleteBuffers(1, &VBO_bones);



	//delete mesh;

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

}



void MeshRenderer::Initialize()
{
	

	
}

Mesh& MeshRenderer::GetMesh()
{
	return *mesh;
}

void MeshRenderer::Render(Camera& cam)
{	
	mesh->Render(cam);
}