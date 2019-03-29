#pragma once
#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "..\Core\Application.h"
#include "..\Components\Renderer.h"

#include <map>



class RenderingEngine 
{
public:
	static RenderingEngine& Instance();
	~RenderingEngine();

	void Initialize();
	void RenderBuffer(MaterialType mt = DEFAULT);
	void RenderBuffer(Camera* camera, MaterialType mt = DEFAULT);	
	void RenderBufferOverrideColor(Camera* camera, glm::vec3 color, MaterialType mt = DEFAULT);

	void SubmitRenderer(Renderer* rend);
	void ClearRendererList();


	static std::vector<Renderer*> allRenderers;


private:

	Material material;
	RenderingEngine();


	RenderingEngine& operator=(const RenderingEngine& e) = delete;
	RenderingEngine(const RenderingEngine& e) = delete;


	void RenderVector(Camera& cam, std::vector<Renderer*>& r, MaterialType m = MaterialType::DEFAULT);
	void RenderVectorOverrideColor(Camera& cam, std::vector<Renderer*>& r, glm::vec3 color,MaterialType m = MaterialType::DEFAULT);

	//void RenderVector(Camera& cam, std::vector<Renderer*>& r, Material* forcedMaterial);

};
