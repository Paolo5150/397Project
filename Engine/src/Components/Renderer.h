#pragma once
#include "..\GameObject\Component.h"
#include "..\Graphics\Material.h"
#include <map>

class Camera;

class Renderer : public Component
	{
	public:
		friend class RenderingEngine;
		Renderer(std::string name, Material m);
		virtual ~Renderer() {};

		virtual void Render(Camera& cam) = 0;
		
		void OnPreRender(Camera& cam, Shader* currentShader = nullptr) override;


		void SendDataToShader(Camera& cam);

		void Update() override;
		Material& GetMaterial(MaterialType materialType = PRIMARY);
		void SetMaterial(Material m, MaterialType = PRIMARY);

		bool isCullable;

	protected:
		std::map<int, Material> allMaterials;

	private:
		bool submitted;


	};

