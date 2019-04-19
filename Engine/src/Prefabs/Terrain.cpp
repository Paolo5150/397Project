#include "Terrain.h"
#include "..\Utils\AssetLoader.h"
#include "..\Graphics\Layers.h"
#include "..\Utils\Maths.h"
#include "..\Lighting\LightingManager.h"
#include "..\Core\Input.h"

Terrain::Terrain(int size) : GameObject("Terrain"), terrainSize(size)
{


	Material material;
	material.SetShader(AssetLoader::Instance().GetAsset<Shader>("Terrain"));
	material.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("ground"));
	material.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("grass"),TextureUniform::DIFFUSE1);
	material.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("rock"),TextureUniform::DIFFUSE2);
	material.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("hm1"), TextureUniform::SPECIAL0);
	material.Loadtexture(AssetLoader::Instance().GetAsset<Texture2D>("rockNormal"), TextureUniform::NORMAL0);	

	material.LoadFloat("UVScale", 50.0f);
	material.LoadFloat("shininess", 18.0f);
	material.LoadFloat("u_maxHeight", transform.GetScale().y);


	SetLayer(0);
	SetLayer(Layers::TERRAIN);

	isWireframe = 0;

	Mesh*m = new GridMesh(size, size);
	meshRenderer = new MeshRenderer(m, material);
	meshRenderer->SetMaterial(material);
	meshRenderer->SetIsCullable(false);
	meshRenderer->GetMaterial(MaterialType::NOLIGHT).SetShader(AssetLoader::Instance().GetAsset<Shader>("TerrainNoLight"));
	meshRenderer->GetMaterial(MaterialType::NOLIGHT).LoadVec3("color", 0.7, 0.7, 0.7);

	meshRenderer->AddPreRenderCallback(std::bind(&Terrain::OnPreRender, this, std::placeholders::_1, std::placeholders::_2));
	meshRenderer->AddPostRenderCallback(std::bind(&Terrain::OnPostRender, this, std::placeholders::_1, std::placeholders::_2));

	meshRenderer->SetIsCullable(false);

	this->AddComponent(meshRenderer);
}

void Terrain::OnPreRender(Camera& cam, Shader* s)
{
	if (Input::GetKeyPressed(GLFW_KEY_K))
		isWireframe = !isWireframe;

	if (isWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	s->SetFloat("u_maxHeight", transform.GetScale().y);
	s->SetFloat("shadowMapCount", LightManager::Instance().GetShadowMapsCount());

	if (s->name == "Terrain")
	 LightManager::Instance().SendShadowToShader(meshRenderer->GetMaterial().GetShader());

}

void Terrain::OnPostRender(Camera& cam, Shader* s)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

float TriangleBaric(glm::vec3 p1, glm::vec3 p2,glm::vec3 p3, glm::vec2 pos)
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p3.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z) )/ det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

float Terrain::GetHeightAt(int worldX, int worldZ)
{
	transform.Update();

	glm::vec3 local = glm::inverse(transform.GetMatrix()) * glm::vec4(worldZ, 0, worldX, 1.0);

	int index = local.z * terrainSize + local.x;
	glm::vec3 v = (meshRenderer->GetMesh().vertices[index ].position);
	v = transform.GetMatrix() * glm::vec4(v.x, v.y, v.z, 1.0);

	int terrainZ = worldX/transform.GetScale().x - transform.GetPosition().x;
	int terrainX = worldZ/ transform.GetScale().z - transform.GetPosition().z;

	float gridSuqareSize = terrainSize / (float)meshRenderer->GetMesh().vertices.size()-1;

	int gridX = -glm::floor(terrainX / gridSuqareSize);
	int gridZ = -glm::floor(terrainZ / gridSuqareSize);


	float h1 = TriangleBaric(meshRenderer->GetMesh().vertices[gridZ * terrainSize + gridX].position,
		meshRenderer->GetMesh().vertices[gridZ * terrainSize + gridX+1].position,
		meshRenderer->GetMesh().vertices[(gridZ+1) * terrainSize + gridX].position,
		glm::vec2(worldX / transform.GetScale().x, worldZ/ transform.GetScale().x));

	/*float h2 = TriangleBaric(meshRenderer->GetMesh().vertices[gridZ * terrainSize + gridX].position,
		meshRenderer->GetMesh().vertices[gridZ * terrainSize + gridX + 1].position,
		meshRenderer->GetMesh().vertices[(gridZ + 1) * terrainSize + gridX+1].position,
		glm::vec2(worldX / transform.GetScale().x, worldZ / transform.GetScale().x));*/

	return (h1) * transform.GetScale().y;
	
}


void Terrain::GetCenter(int& x, int& y,int& z)
{
	transform.Update();

	int xr = this->terrainSize / 2;
	int xz = terrainSize / 2;
	glm::vec3 v = (meshRenderer->GetMesh().vertices[((xz) *terrainSize) + xr].position);
	v = transform.GetMatrix() * glm::vec4(v.x, v.y, v.z, 1.0);

	x = v.x;
	y = v.y;
	z = v.z;
}


/*bool Terrain::GenerateFaultFormation(int iterations, int minHeight, float weight, bool random)
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
	meshRenderer->GetArrayBufferVertex().AddData(meshRenderer->GetMesh().vertices);
	transform.Translate(-meshRenderer->GetMesh().GetCenter().x, -meshRenderer->GetMesh().GetCenter().y, -meshRenderer->GetMesh().GetCenter().z);
}*/


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

void Terrain::ApplyHeightMap(std::string texturePath)
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

		float min = 50000;
		float max = -5000;
		for (int j = 0; j < terrainSize; j++)
		{
			for (int i = 0; i < terrainSize; i++)
			{
				
				meshRenderer->GetMesh().vertices[(j*terrainSize) + i].position.y = heights[(width * (width * j / terrainSize)) + (width * i / terrainSize)] ;
				
				/*if (i > 0 && i < 60)
					{
				
					float higher = i / 30.0f;
					if (i>30)
						higher = 2 - higher;

					higher *= 0.8;
					meshRenderer->GetMesh().vertices[(j*terrainSize) + i].position.y += higher;
					}

				if (j > 0 && j < 60)
				{

					float higher = j / 30.0f;
					if (j>30)
						higher = 2 - higher;

					meshRenderer->GetMesh().vertices[(j*terrainSize) + i].position.y += higher;
				}

				if (i > terrainSize - 60 && i < terrainSize)
				{

					float higher = i / 30.0f;
					if (i>30)
						higher = 2 - higher;

					higher *= 0.8;
					meshRenderer->GetMesh().vertices[(j*terrainSize) + i].position.y += higher;
				}

				if (j > 0 && j < 60)
				{

					float higher = j / 30.0f;
					if (j>30)
						higher = 2 - higher;

					meshRenderer->GetMesh().vertices[(j*terrainSize) + i].position.y += higher;
				}*/


				min = meshRenderer->GetMesh().vertices[(j*terrainSize) + i].position.y < min ? meshRenderer->GetMesh().vertices[(j*terrainSize) + i].position.y : min;
				max = meshRenderer->GetMesh().vertices[(j*terrainSize) + i].position.y > max ? meshRenderer->GetMesh().vertices[(j*terrainSize) + i].position.y : max;

			}
		}



		meshRenderer->GetMesh().CalculateNormals();
		meshRenderer->GetArrayBufferVertex().AddData(meshRenderer->GetMesh().vertices);
		//transform.Translate(-meshRenderer->GetMesh().GetCenter().x, -meshRenderer->GetMesh().GetCenter().y, -meshRenderer->GetMesh().GetCenter().z);
		delete[] heights;
	}

}

float Terrain::GetTerrainMaxX()
{
	return meshRenderer->GetMesh().vertices[((terrainSize - 1) * terrainSize) + (terrainSize - 1)].position.x * transform.GetScale().x;
}
float Terrain::GetTerrainMinX()
{
	return meshRenderer->GetMesh().vertices[(0 * terrainSize) + 0].position.x * transform.GetScale().x* transform.GetScale().x;
}

float Terrain::GetTerrainMaxZ()
{
	return meshRenderer->GetMesh().vertices[((terrainSize - 1) * terrainSize) + (terrainSize - 1)].position.z * transform.GetScale().z;
}
float Terrain::GetTerrainMinZ()
{
	return meshRenderer->GetMesh().vertices[(0 * terrainSize) + 0].position.x * transform.GetScale().z* transform.GetScale().z;
}

