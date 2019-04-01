#include "Terrain.h"
#include "..\Utils\AssetLoader.h"
#include "..\Graphics\Layers.h"
#include "..\Utils\Maths.h"


Terrain::Terrain(int size) : GameObject("Terrain"), terrainSize(size)
{


	Material material;
	material.SetShader(AssetLoader::Instance().GetAsset<Shader>("Terrain"));
	material.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("ground"));
	material.LoadFloat("UVScale", 18.0f);

	SetLayer(0);
	SetLayer(Layers::TERRAIN);

	Mesh*m = new GridMesh(size, size);
	meshRenderer = new MeshRenderer(m, material);
	meshRenderer->AddPreRenderCallback(std::bind(&Terrain::OnPreRender, this, std::placeholders::_1, std::placeholders::_2));
	meshRenderer->isCullable = false;

	this->AddComponent(meshRenderer);
}

void Terrain::OnPreRender(Camera& cam, Shader* s)
{

}

bool Terrain::GenerateFaultFormation(int iterations, int minHeight, int maxHeight, float weight, bool random)
{
	int x1, x2, z1, z2;
	float* heights = NULL;
	int displacement;

	if (random) //create truly random map
		srand(time(NULL));
	// allocate memory for heightfield array

	heights = new float[terrainSize*terrainSize]; //allocate memory


	if (heights == NULL)
		return false;// initialise the heightfield array to all zeros

	for (int i = 0; i < terrainSize*terrainSize; i++)
		heights[i] = 0;

	// generate heightfield
	for (int j = 0; j < iterations; j++) {
		//calculate reducing displacement value - how much to alter height
		displacement = maxHeight - ((maxHeight - minHeight)*j) / iterations;
		//pick the first point P1(x1, z1) at random from the height map
		x1 = (rand() % terrainSize);
		z1 = (rand() % terrainSize);
		// pick up the second random point P2(x2, z2) and make sure it is
		// different from the first point
		do {
			x2 = (rand() % terrainSize);
			z2 = (rand() % terrainSize);
		} while (x2 == x1 && z2 == z1);
		//for each point P(x, z) in the field, calculate the new height values
		for (int z = 0; z < terrainSize; z++) {
			for (int x = 0; x < terrainSize; x++) {
				// determine which side of the line P1P2 the point P lies in
				if (((x - x1) * (z2 - z1) - (x2 - x1) * (z - z1)) > 0) {
					heights[(z*terrainSize) + x] += (float)displacement;
				}
			}
		}
		AddFilter(heights, weight,terrainSize);
	}
	// normalise the heightfield
	NormaliseTerrain(heights, terrainSize, terrainSize);

	for (int j = 0; j < terrainSize; j++)
	{
		for (int i = 0; i < terrainSize; i++)
		{		
			meshRenderer->GetMesh().vertices[(j*terrainSize) + i].position.y = heights[(j*terrainSize) + i] * maxHeight;
		}
	}
	Logger::LogInfo("Center",Maths::Vec3ToString(meshRenderer->GetMesh().GetCenter()));
	meshRenderer->GetMesh().CalculateNormals();
	meshRenderer->vertexBuffer->AddData(meshRenderer->GetMesh().vertices);
	transform.Translate(-meshRenderer->GetMesh().GetCenter().x, -meshRenderer->GetMesh().GetCenter().y, -meshRenderer->GetMesh().GetCenter().z);
}


void Terrain::NormaliseTerrain(float* heightData, int dataWidth, int dataHeight)
{
	float fMin, fMax;
	float fHeight;
	int i;
	fMin = heightData[0];
	fMax = heightData[0];
	//find the min/max values of the height terrainData
	for (i = 1; i < dataWidth*dataHeight; i++) {
		if (heightData[i] > fMax)
			fMax = heightData[i];
		else if (heightData[i] < fMin)
			fMin = heightData[i];
	}
	//find the range of the altitude
	if (fMax <= fMin)
		return;
	fHeight = fMax - fMin;
	//scale the values to a range of 0-255
	for (i = 0; i < dataWidth*dataHeight; i++)
		heightData[i] = ((heightData[i] - fMin) / fHeight);

}
void Terrain::AddFilter(float* heightData, float weight, int size)
{
	int i;
	//erode left to right, starting at the beginning of each row
	for (i = 0; i < size; i++)
		FilterPass(&heightData[size*i], 1, weight,size);
	//erode right to left, starting at the end of each row
	for (i = 0; i < size; i++)
		FilterPass(&heightData[size*i + size - 1], -1, weight, size);
	//erode top to bottom, starting at the beginning of each column
	for (i = 0; i < size; i++)
		FilterPass(&heightData[i], size, weight, size);
	//erode from bottom to top, starting from the end of each column
	for (i = 0; i < size; i++)
		FilterPass(&heightData[size*(size - 1) + i], -size, weight, size);

}
void Terrain::FilterPass(float* dataP, int increment, float weight, int size)
{

	float yprev = *dataP; // the starting point in the terrain array
	int j = increment; // +1, -1, +size, -size
	float k = weight;

	for (int i = 1; i < size; i++) {
		// yi = k yi-1 + (1-k) xi
		*(dataP + j) = k * yprev + (1 - k)*(*(dataP + j)); //
		yprev = *(dataP + j);
		j += increment;
	}

}
unsigned char* getColorAtPixel(unsigned char* image, size_t x, size_t y, size_t width, int elementsPerPixel = 3) { // 1 for R, 2 for RG, 3 for RGB, 4 for RBGA
	return (image + (y * width + x) *1);
}

void Terrain::ApplyHeightMap(std::string texturePath, float maxHeight)
{
	
	int width, height;
	unsigned char* terrainData = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_L);

	//AssetLoader::Instance().ReadHeightmapData(texturePath, terrainData, width, height);

	if (terrainData)
	{
		Logger::LogInfo("Loading hm",width);
		float* heights = new float[width * height];;
		
		int index = 0;


		int count = 0;
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				int index = i * height + j;

				float rgb = *getColorAtPixel(terrainData, i, j, width, 3);
				heights[index] = rgb;
				//Logger::LogInfo("Height", rgb);

				count++;
			}
		}

		for (int i = 0; i < 20; i++)
			AddFilter(heights, 0.2f, width);

		NormaliseTerrain(heights,width,height);

		stbi_image_free(terrainData);


		for (int j = 0; j < terrainSize; j++)
		{
			for (int i = 0; i < terrainSize; i++)
			{
				int inted = ((j)*width) + i;

				meshRenderer->GetMesh().vertices[(j*terrainSize) + i].position.y = heights[(width * (width * j / terrainSize)) + (width * i / terrainSize)] * maxHeight;
			}
		}
		//Logger::LogInfo("Center", Maths::Vec3ToString(meshRenderer->GetMesh().GetCenter()));
		meshRenderer->GetMesh().CalculateNormals();
		meshRenderer->vertexBuffer->AddData(meshRenderer->GetMesh().vertices);
		transform.Translate(-meshRenderer->GetMesh().GetCenter().x, -meshRenderer->GetMesh().GetCenter().y, -meshRenderer->GetMesh().GetCenter().z);
		delete[] heights;
	}
}