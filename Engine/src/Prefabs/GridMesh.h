#pragma once
#include "..\Graphics\Mesh.h"

class GridMesh : public Mesh
{
public:
	GridMesh(int widthVets, int depthVerts);
	~GridMesh();
	int GetSizeX() { return sizeX; };
	int GetSizeZ() { return sizeZ; };

	int sizeX;
	int sizeZ;

private:
	void Initialize();

};
