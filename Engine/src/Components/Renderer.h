#pragma once
#include "..\GameObject\Component.h"
#include "..\Graphics\Material.h"
#include <map>
#include <functional>
#include <vector>

class Camera;
class Shader;

class Renderer : public Component
	{
	public:
		friend class RenderingEngine;

		Renderer(std::string name, Material m);
		Renderer(std::string name);

		virtual ~Renderer() {};

		virtual void Render(Camera& cam) = 0;
		
		void OnPreRender(Camera& cam, Shader* currentShader = nullptr) override;


		void SendDataToShader(Camera& cam);

		void Update() override;
		void EngineUpdate() override;

		
		Material& GetMaterial(MaterialType materialType = DEFAULT);
		void SetMaterial(Material m, MaterialType = DEFAULT);

		void AddPreRenderCallback(std::function<void(Camera&, Shader*)> cb);
		void AddPostRenderCallback(std::function<void(Camera&, Shader*)> cb);


		bool isCullable;

	protected:
		std::map<int, Material> allMaterials;
		std::vector<std::function<void(Camera&, Shader*)>> preRenderCallbacks;
		std::vector<std::function<void(Camera&, Shader*)>> postRenderCallbacks;
		bool submitted;



	private:
		void CreateOtherMaterials(Material& defaultMat);


	};

