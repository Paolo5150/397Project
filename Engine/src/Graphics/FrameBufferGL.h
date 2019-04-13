#pragma once
#include "FrameBuffer.h"
#include "..\Core\Window.h"

/**
* @class FrameBuffer
* @brief Specialized class for a custom frame buffer for Opengl
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2018
*
*
* @bug No known bugs.
*/
class FrameBufferGL : public FrameBuffer
{
public:
	/**
	* @brief				Create a new frame buffer
	*
	* @pre					The graphics API object must exist
	* @post					A new frame buffer object is created
	* @param w				The width of the buffer texture
	* @param h				The height of the buffer texture
	* @param hasColorAttachment		Whether the frame buffer has a color attachment
	*/
	FrameBufferGL(int w, int h, bool hasColorAttachment = true);

	/**
	* @brief				Destroy the frame buffer
	*
	* @pre					The frame buffer must exist
	* @post					The frame buffer is destroyed

	*/
	~FrameBufferGL();

	/**
	* @brief				Bind the frame buffer
	*
	* @pre					The frame buffer must exist
	* @post					The frame buffer is ready to be used
	*/
	void Bind();


	/**
	* @brief				Unbind the frame buffer and bind the default frame buffer (screen)
	*						Reset the viewport to screen size
	* @pre					The frame buffer must exist
	* @post					The frame buffer is disabled
	*/
	void Unbind();

	/**
	* @brief				Resize the texture
	* @pre					The frame buffer must exist
	* @post					The texture of the frame buffer is resizedd
	* @param w				The width of the texture
	* @param h				The height of the texture

	*/
	void ResizeTexture(int w, int h) override;




};
