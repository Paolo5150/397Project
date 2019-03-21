#include "Quad.h"



QuadMesh::QuadMesh()
{

	Initialize();
}

QuadMesh::~QuadMesh()
{

}

void QuadMesh::Initialize()
{

	Vertex v1(-1, -1, 0);
	v1.UV = glm::vec2(0, 0);

	Vertex v2(1, -1, 0);
	v2.UV = glm::vec2(1, 0);

	Vertex v3(1, 1, 0);
	v3.UV = glm::vec2(1, 1);

	Vertex v4(-1, 1, 0);
	v4.UV = glm::vec2(0, 1);

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);


	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);


	//CalculateNormals();


}