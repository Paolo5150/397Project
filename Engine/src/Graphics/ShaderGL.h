#pragma once
#include "Shader.h"
#include "GL/glew.h"

class ShaderGL : public Shader
{
public: 
	friend class API_Opengl;
	~ShaderGL();

	void Bind();
	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;
	void SetMat4(const std::string &name, glm::mat4 value) const;
	void SetVec3(const std::string &name, glm::vec3 value) const;
	void SetVec4(const std::string &name, glm::vec4 value) const;
	void AssignToUniformBuffer(std::string uniformName, unsigned bufferIndex);


private:
	ShaderGL(std::string name, std::string vSource, std::string fSource);
	ShaderGL(){}

	bool CompileShader(unsigned int& sid, const char* source, GLenum type);





};

