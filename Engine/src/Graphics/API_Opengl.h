#pragma once
#include "GraphicsAPI.h"
#include <GL/glew.h>

class API_Opengl : public GraphicsAPI
{
public:
	API_Opengl();
	~API_Opengl();

	virtual void Initialize();
	virtual void Shutdown();
	void ClearColorBuffer() ;
	void ClearDepthBuffer() ;
	void SetViewPort(int w, int h);

};