#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vs, std::vector<unsigned> inds, bool calculateNormals)
{
	vertices = vs;
	indices = inds;

	if (calculateNormals)
		CalculateNormals();
}

Mesh::~Mesh()
{

}

glm::vec3 Mesh::GetCenter()
{
	glm::vec3 center;

	for (int i = 0; i < vertices.size(); i++)
	{
		center += vertices[i].position;

	}

	center /= vertices.size();
	return center;

}



void Mesh::CalculateNormals()
{
	if (indices.size() > 3)
	{

		for (unsigned int i = 0; i < indices.size() - 2; i += 3)
		{
			//Normals
			glm::vec3 v1v2 = vertices[indices[i + 1]].position - vertices[indices[i]].position;
			glm::vec3 v1v3 = vertices[indices[i + 2]].position - vertices[indices[i]].position;
			glm::vec3 cross = glm::normalize(glm::cross(v1v2, v1v3));


			vertices[indices[i]].normal = cross;
			vertices[indices[i + 1]].normal = cross;
			vertices[indices[i + 2]].normal = cross;

			//Tangent and binormal
			glm::vec2 deltaUV1 = vertices[indices[i + 1]].UV - vertices[indices[i]].UV;
			glm::vec2 deltaUV2 = vertices[indices[i + 2]].UV - vertices[indices[i]].UV;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

			glm::vec3 test = r * ((v1v2 * deltaUV2.y) - (v1v3 * deltaUV1.y));

			vertices[indices[i]].tangent = r * ((v1v2 * deltaUV2.y) - (v1v3 * deltaUV1.y));
			vertices[indices[i + 1]].tangent = r * ((v1v2 * deltaUV2.y) - (v1v3 * deltaUV1.y));
			vertices[indices[i + 2]].tangent = r * ((v1v2 * deltaUV2.y) - (v1v3 * deltaUV1.y));

			vertices[indices[i]].binormal = r * ((v1v3 * deltaUV1.x) - (v1v2 * deltaUV2.x));
			vertices[indices[i + 1]].binormal = r * ((v1v3 * deltaUV1.x) - (v1v2 * deltaUV2.x));
			vertices[indices[i + 2]].binormal = r * ((v1v3 * deltaUV1.x) - (v1v2 * deltaUV2.x));

		}
	}
}

void VertexBoneData::addBoneData(unsigned bone_id, float weight)
{
	/*for (unsigned i = 0; i < NUM_BONES_PER_VEREX; i++)
	{
		if (weights[i] == 0.0)
		{
			ids[i] = bone_id;
			weights[i] = weight;

			return;
		}
	}*/

}