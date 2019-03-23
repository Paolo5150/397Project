#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Vertex
{
public:

	Vertex() {}
	Vertex(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}

	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 UV;
	glm::vec3 color;
	glm::vec3 tangent;
	glm::vec3 binormal;

};