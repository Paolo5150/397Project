#pragma once

#include <vector>
#include "Vertex.h"
#include "..\Core\Logger.h"
#include <vector>



#define NUM_BONES_PER_VEREX 4

	struct MeshFace
	{
		Vertex* v1;
		Vertex* v2;
		Vertex* v3;

		MeshFace(Vertex v1, Vertex v2, Vertex v3) : v1(&v1), v2(&v2), v3(&v3){};

	};

	// Used for skeletal animation
	struct VertexBoneData
	{
		unsigned ids[NUM_BONES_PER_VEREX];   // we have 4 bone ids for EACH vertex & 4 weights for EACH vertex
		float weights[NUM_BONES_PER_VEREX];
		int added;
		VertexBoneData()
		{
			added = 0;
			memset(ids, 0, sizeof(ids));    // init all values in array = 0
			memset(weights, 0, sizeof(weights));
		}

		void addBoneData(unsigned bone_id, float weight);
	};
	class Mesh
	{
	public:
		Mesh() {}
		Mesh(std::vector<Vertex> vs, std::vector<unsigned> indices, bool calculateNormals = false);
		virtual ~Mesh();
		std::vector<Vertex> vertices;
		std::vector<unsigned> indices;

		glm::vec3 GetCenter();
		std::vector<VertexBoneData> bones_id_weights_for_each_vertex;
		void CalculateNormals();


	protected:

	};
