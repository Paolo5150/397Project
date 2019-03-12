#pragma once

#include "GL/glew.h"
#include "..\Utils\Asset.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.inl>
#include "..\Core\Logger.h"

class Shader  : public Asset
{
public:

	virtual ~Shader(){
		Logger::LogError("Shader", name, "just died");
	};


	virtual void Bind() = 0;
	virtual void SetBool(const std::string &name, bool value) const = 0;
	virtual void SetInt(const std::string &name, int value) const = 0;
	virtual void SetFloat(const std::string &name, float value) const = 0;
	virtual void SetMat4(const std::string &name, glm::mat4 value) const = 0;
	virtual void SetVec3(const std::string &name, glm::vec3 value) const = 0;
	virtual void SetVec4(const std::string &name, glm::vec4 value) const = 0;
	virtual void AssignToUniformBuffer(std::string uniformName, unsigned bufferIndex) = 0;


	Shader(std::string vertexSource, std::string fragSource){};
	Shader(){}
	protected :
	unsigned shaderID;
	bool CompileShader(unsigned int& sid, const char* source, GLenum type);





};

