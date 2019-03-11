
#include "ShaderGL.h"
#include <assert.h>


ShaderGL::ShaderGL(std::string vertexFullPath, std::string fragmentFullPath)
{
	std::string vertexFileContent = FileUtils::ReadFileToString(vertexFullPath);
	std::string fragFileContent = FileUtils::ReadFileToString(fragmentFullPath);


	const char* vertexSource = vertexFileContent.c_str();
	const char* fragmentSource = fragFileContent.c_str();



	unsigned int vertexID, fragmentID;
	bool result = true;
	char infoLog[512];

	if (!CompileShader(vertexID, vertexSource, GL_VERTEX_SHADER))
	{

		glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
		Logger::LogError("Could not compile VERTEX shader:",vertexFullPath,". Error:",std::string(infoLog));

		result = false;
	}

	if (!CompileShader(fragmentID, fragmentSource, GL_FRAGMENT_SHADER))
	{

		glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
		Logger::LogError("Could not compile FRAGMENT shader:", fragmentFullPath, ". Error:", std::string(infoLog));
		
		result = false;
	}

	//assert(result && "Could not compile shader");

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexID);
	glAttachShader(shaderID, fragmentID);
	glLinkProgram(shaderID);

	int success;

	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
	}

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);


}


ShaderGL::~ShaderGL()
{




}

bool ShaderGL::CompileShader(unsigned int& sid, const char* source, GLenum type)
{
	int success;

	sid = glCreateShader(type);
	glShaderSource(sid, 1, &source, NULL);
	glCompileShader(sid);
	glGetShaderiv(sid, GL_COMPILE_STATUS, &success);

	return success != 0;

}


void ShaderGL::Activate()
{
	glUseProgram(shaderID);

}


void ShaderGL::SetBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
}
void ShaderGL::SetInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}
void ShaderGL::SetFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}

void ShaderGL::SetMat4(const std::string &name, glm::mat4 value) const
{
	int location = glGetUniformLocation(shaderID, name.c_str());
	glUseProgram(shaderID);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderGL::SetVec3(const std::string &name, glm::vec3 v) const
{
	int location = glGetUniformLocation(shaderID, name.c_str());
	glUseProgram(shaderID);
	glUniform3f(location, v.x, v.y, v.z);

}

void ShaderGL::SetVec4(const std::string &name, glm::vec4 v) const
{
	int location = glGetUniformLocation(shaderID, name.c_str());
	glUseProgram(shaderID);
	glUniform4f(location, v.x, v.y, v.z, v.w);

}

void ShaderGL::AssignToUniformBuffer(std::string uniformName, GLuint bufferIndex)
{
	int location = glGetUniformBlockIndex(shaderID, uniformName.c_str());
	glUniformBlockBinding(shaderID, location, bufferIndex);
}