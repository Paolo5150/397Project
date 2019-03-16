#pragma once
#include "Texture2D.h"
#include "GL/glew.h"

class Texture2DGL : public Texture2D
{
public:
	friend class API_Opengl;

	void Bind();
	~Texture2DGL();

protected:
	Texture2DGL(){}
	Texture2DGL(std::string textureName, int width, int height, int channels, unsigned char* data);
	Texture2DGL(std::string name,unsigned width, unsigned height, bool isDepth = false);



};
