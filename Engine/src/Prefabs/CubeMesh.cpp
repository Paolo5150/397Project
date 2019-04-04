#include "CubeMesh.h"




CubeMesh::CubeMesh()
{

	Initialize();
}

CubeMesh::~CubeMesh()
{

}

void CubeMesh::Initialize()
{
	//Front
	Vertex v1(-1, -1, 1);
	v1.UV = glm::vec2(0, 0);

	Vertex v2(-1, 1, 1);
	v2.UV = glm::vec2(0, 1);

	Vertex v3(1, 1, 1);
	v3.UV = glm::vec2(1, 1);

	Vertex v4(1, -1, 1);
	v4.UV = glm::vec2(1, 0);


	//Back
	Vertex v5(-1, -1, -1);
	v5.UV = glm::vec2(1, 0);

	Vertex v6(1, -1, -1);
	v6.UV = glm::vec2(0, 0);

	Vertex v7(1, 1, -1);
	v7.UV = glm::vec2(0, 1);

	Vertex v8(-1, 1, -1);
	v8.UV = glm::vec2(1, 1);


	//Right
	Vertex v9(1, -1, -1);
	v9.UV = glm::vec2(0, 0);

	Vertex v10(1, -1, 1);
	v10.UV = glm::vec2(1, 0);

	Vertex v11(1, 1, 1);
	v11.UV = glm::vec2(1, 1);

	Vertex v12(1, 1, -1);
	v12.UV = glm::vec2(0, 1);


	//Left
	Vertex v13(-1, -1, 1);
	v13.UV = glm::vec2(0, 1);

	Vertex v14(-1, -1, -1);
	v14.UV = glm::vec2(0, 1);

	Vertex v15(-1, 1, -1);
	v15.UV = glm::vec2(0, 1);

	Vertex v16(-1, 1, 1);
	v16.UV = glm::vec2(0, 1);

	//Top
	Vertex v17(-1, 1, 1);
	v17.UV = glm::vec2(0, 1);

	Vertex v18(-1, 1, -1);
	v18.UV = glm::vec2(0, 1);

	Vertex v19(1, 1, -1);
	v19.UV = glm::vec2(0, 1);

	Vertex v20(1, 1, 1);
	v20.UV = glm::vec2(0, 1);


	//Bottom
	Vertex v21(-1, -1, 1);
	v21.UV = glm::vec2(0, 1);

	Vertex v22(1, -1, 1);
	v22.UV = glm::vec2(0, 1);

	Vertex v23(1, -1, -1);
	v23.UV = glm::vec2(0, 1);

	Vertex v24(-1, -1, -1);
	v24.UV = glm::vec2(0, 1);




	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v7);
	vertices.push_back(v8);
	vertices.push_back(v9);
	vertices.push_back(v10);
	vertices.push_back(v11);
	vertices.push_back(v12);
	vertices.push_back(v13);
	vertices.push_back(v14);
	vertices.push_back(v15);
	vertices.push_back(v16);
	vertices.push_back(v17);
	vertices.push_back(v18);
	vertices.push_back(v19);
	vertices.push_back(v20);
	vertices.push_back(v21);
	vertices.push_back(v22);
	vertices.push_back(v23);
	vertices.push_back(v24);

	//Front
	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);

	//Back
	indices.push_back(4);
	indices.push_back(7);
	indices.push_back(6);
	indices.push_back(6);
	indices.push_back(5);
	indices.push_back(4);

	//Right
	indices.push_back(8);
	indices.push_back(11);
	indices.push_back(10);
	indices.push_back(10);
	indices.push_back(9);
	indices.push_back(8);

	//Right
	indices.push_back(12);
	indices.push_back(15);
	indices.push_back(14);
	indices.push_back(14);
	indices.push_back(13);
	indices.push_back(12);

	//Top
	indices.push_back(16);
	indices.push_back(19);
	indices.push_back(18);
	indices.push_back(18);
	indices.push_back(17);
	indices.push_back(16);

	//Bottom
	indices.push_back(20);
	indices.push_back(23);
	indices.push_back(22);
	indices.push_back(22);
	indices.push_back(21);
	indices.push_back(20);






	CalculateNormals();


}