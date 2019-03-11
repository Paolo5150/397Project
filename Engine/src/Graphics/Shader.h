#pragma once

#include "..\Core\Core.h"
#include "..\Utils\FileUtils.h"
#include <string>
#include <map>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.inl>

class Shader
{
public:


	Shader()
	{
		
	}

	~Shader(){};
	unsigned GetID(){ return shaderID;};

	virtual void Activate(){};
	virtual void SetBool(const std::string &name, bool value) const{};
	virtual void SetInt(const std::string &name, int value) const{};
	virtual void SetFloat(const std::string &name, float value) const{};
	virtual void SetMat4(const std::string &name, glm::mat4 value) const{};
	virtual void SetVec3(const std::string &name, glm::vec3 value) const{};
	virtual void SetVec4(const std::string &name, glm::vec4 value) const{};
	virtual void AssignToUniformBuffer(std::string uniformName, GLuint bufferIndex){};


protected:
	GLuint shaderID;
	

	



};

