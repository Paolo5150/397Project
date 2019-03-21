#include "Material.h"

std::string Material::textureUniforms[] = {
	"diffuse0",
	"diffuse1",
	"diffuse2",
	"normal0",
	"normal1",
	"emissive0",
	"ambient0",
	"specular0",
	"reflection0",
	"special0",
	"special0",
	"special0" };


Material::Material()
{
	PreloadMaterial();

}

Material::Material(Shader* s)
{
	shader = s;
	PreloadMaterial();

}

Material::~Material()
{}

void Material::SetReflectivity(float r)
{
	reflectivity = r;
	LoadFloat("reflectivity", reflectivity);
}

void Material::PreloadMaterial()
{
	materialGroup = OPA;

	LoadVec3("color", glm::vec3(1, 1, 1));
	LoadFloat("shininess", 32);
	LoadFloat("UVscale", 1.0);
	//LoadFloat("alpha", 1.0);
	LoadFloat("textureTransparency", 0.0);
	SetReflectivity(0.0f);



}

void Material::LoadVec4(std::string name, glm::vec4 v)
{
	vec4s["material." + name] = v;
}

void Material::LoadVec3(std::string name, glm::vec3 v)
{
	vec3s["material." + name] = v;
}

//Temporary
void Material::LoadMat4(std::string name, glm::mat4 v)
{
	mat4s[name] = v;
}

void Material::LoadFloat(std::string name, float v)
{
	floats["material." + name] = v;
}


/*void Material::LoadCubemap(Cubemap* t, TextureUniform tu)
{

	//Check if texture is already loaded
	auto it = cubemaps.begin();

	for (; it != cubemaps.end(); it++)
	{
		if (it->second == t)
		{
			return;
		}
	}

	//Check to see if the uniform is already loaded, in case save to next slot in map
	auto un = cubemaps.find(tu);

	if (un != cubemaps.end())
	{
		cubemaps[(tu + 1)] = t;
	}
	else
		cubemaps[tu] = t;
}*/

void Material::Loadtexture(Texture2D* t, TextureUniform tu)
{
	if (textures.size() >= 16)
		return;
	//Check if texture is already loaded
	auto it = textures.begin();

	for (; it != textures.end(); it++)
	{
		if (it->second == t)
		{
			return;
		}
	}

	//Check to see if the uniform is already loaded, in case save to next slot in map
	auto un = textures.find(tu);

	if (un != textures.end())
	{
		textures[(tu + 1)] = t;
	}
	else
		textures[tu] = t;


}

void Material::BindMaterial()
{
	shader->Bind(); //This line is kind of vital
	auto it = textures.begin();

	//TODO: improc ve this, cubemap and texture can be bind together, should not be the case
	for (; it != textures.end(); it++)
	{
		glActiveTexture(GL_TEXTURE0 + it->first);
		it->second->Bind();
		shader->SetInt(textureUniforms[it->first], it->first);



	}

	/*for (auto cit = cubemaps.begin(); cit != cubemaps.end(); cit++)
	{
		glActiveTexture(GL_TEXTURE0 + cit->first);
		cit->second->Bind();
		shader->SetInt(textureUniforms[cit->first], cit->first);



	}*/


	auto vit = vec3s.begin();

	for (; vit != vec3s.end(); vit++)
	{
		shader->SetVec3(vit->first, vit->second);
	}

	auto vit2 = vec4s.begin();

	for (; vit2 != vec4s.end(); vit2++)
	{
		shader->SetVec4(vit2->first, vit2->second);
	}

	auto vit3 = floats.begin();

	for (; vit3 != floats.end(); vit3++)
	{
		shader->SetFloat(vit3->first, vit3->second);
	}

	auto matit = mat4s.begin();

	for (; matit != mat4s.end(); matit++)
	{
		shader->SetMat4(matit->first, matit->second);
	}


}

void Material::UnbindMaterial()
{

	auto it = textures.begin();

	for (; it != textures.end(); it++)
	{
		glActiveTexture(GL_TEXTURE0 + it->first);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE);
		//shader->SetInt(textureUniforms[it->first], it->first);



	}

	/*for (auto cit = cubemaps.begin(); cit != cubemaps.end(); cit++)
	{
		glActiveTexture(GL_TEXTURE0 + cit->first);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		shader->SetInt(textureUniforms[cit->first], cit->first);
	}*/

	glActiveTexture(GL_TEXTURE0);

}
