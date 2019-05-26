#pragma once
#include "Renderer.h"
#include "..\Graphics\Mesh.h"
#include "..\Graphics\ArrayBuffer.h"
#include "..\Graphics\VertexArray.h"


/**
* @class LineRenderer
* @brief Specialized Renderer used to draw lines in 3D
*
*
* @author Paolo Ferri
* @version 01
* @date 7/04/2019
*
* @bug No known bugs.
*/


class LineRenderer : public Renderer
{

public:
	friend class RenderingEngine;

	/**
	* @brief		Clean up vertex array from memoery
	*
	* @post			The vertices are removed from memory.
	*
	*/
	~LineRenderer();

	/**
	* @brief		Create LineRenderer component
	*
	* @post			TThe LineRenderer component is created.
	*
	* @param verts The vertices of the line
	*/
	LineRenderer(std::vector<Vertex> verts);

	/**
	* @brief		Renders the line
	*
	* @post			The line is rendered
	*
	* @param cam	The camera used to render the line
	*/
	void Render(Camera& cam) override;

	/**
	* @brief		Callback called right before rendering
	*
	* @param cam	The camera used to render the line
	* @param currentShader The current shader bound
	*/
	void OnPreRender(Camera& cam, Shader* currentShader = nullptr) override;

	/**
	* @brief		Set new vertives for the line
	*
	* @post			The new vertices replace the old ones
	*
	* @param vertes	The new vertices
	*/
	void SetVertices(std::vector<Vertex> verts);

	/**
	* @brief		The line color
	*
	* @post			The line is rendered with the new color
	*
	* @param r The red channel amount (0.0 - 1.0)
	* @param g The green channel amount (0.0 - 1.0)
	* @param b The blue channel amount (0.0 - 1.0)
	*/
	void SetColor(float r, float g, float b);

private:

	/**
	* @brief		The array of vertices on the GPU
	*/
	ArrayBuffer<Vertex>* vertexBuffer;

	/**
	* @brief		The vertex array
	*/
	VertexArray* vertexArray;

	/**
	* @brief		The vertices
	*/
	std::vector<Vertex> vertices;

	/**
	* @brief		Load vertices to GPU
	*/
	void Initialize();

};

