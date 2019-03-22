#pragma once

#include "Texture2D.h"
#include"Shader.h"
#include <map>



	class Model;
	enum TextureUniform
	{
		DIFFUSE0,
		DIFFUSE1,
		DIFFUSE2,
		NORMAL0,
		NORMAL1,
		EMISSIVE0,
		AMBIENT0,
		SPECULAR0,
		REFLECITON0,
		SPECIAL0,
		SPECIAL1,
		SPECIAL2,
	};

	enum MaterialType
	{
		PRIMARY,
		SIMPLIFIED
	};

	enum MaterialRenderingGroup
	{
		OPA,
		TRANS
	};

	class Material
	{

	public:
		friend class MeshMaterial;
		friend class Model;

		std::string name;
		void Loadtexture(Texture2D* t, TextureUniform tu = DIFFUSE0);
		//void LoadCubemap(Cubemap* t, TextureUniform tu = DIFFUSE0);

		Material();
		Material(Shader* s);
		~Material();

		void BindMaterial();
		void UnbindMaterial();
		void SetShader(Shader* s) { shader = s; }
		Shader& GetShader() { return *shader; };
		void LoadVec4(std::string, glm::vec4 v);
		void LoadVec3(std::string, float x, float y, float z);
		void LoadFloat(std::string, float v);
		void LoadMat4(std::string, glm::mat4 v);
		void SetReflectivity(float r);


		MaterialRenderingGroup materialGroup;


		std::map<int, Texture2D*> textures;
	private:
		//std::map<int, Cubemap*> cubemaps;
		float reflectivity;

		Shader* shader;
		std::map<std::string, glm::vec4> vec4s;
		std::map<std::string, glm::vec3> vec3s;
		std::map<std::string, float> floats;
		std::map<std::string, glm::mat4> mat4s;

		void PreloadMaterial();
		static std::string textureUniforms[];


	};
