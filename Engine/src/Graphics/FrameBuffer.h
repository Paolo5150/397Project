#pragma once
#include "Texture2D.h"

/**
* @class FrameBuffer
* @brief Generic class for a custom frame buffer 
*
* Allows to render to a texture
* @author Paolo Ferri
* @version 01
* @date 15/03/2018
*
*
* @bug No known bugs.
*/
class FrameBuffer 
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
	FrameBuffer(int w, int h, bool hasColorAttachment = true){};

	/**
	* @brief				Destroy the frame buffer
	*
	* @pre					The frame buffer must exist
	* @post					The frame buffer is destroyed

	*/
	virtual ~FrameBuffer(){};

	/**
	* @brief				Bind the frame buffer
	*
	* @pre					The frame buffer must exist
	* @post					The frame buffer is ready to be used
	*/
	virtual void Bind() = 0;

	/**
	* @brief				Unbind the frame buffer and bind the default frame buffer (screen)
	*						Reset the viewport to screen size
	* @pre					The frame buffer must exist
	* @post					The frame buffer is disabled
	*/
	virtual void Unbind() = 0;

	/**
	* @brief				Get the color texture
	* @pre					The frame buffer must exist
	* @post					The color texture is returned
	* @return				The color texture
	*/
	Texture2D* GetColorTexture(int index = 0){ return colorAttachments[index]; };

	/**
	* @brief				Get the depth texture
	* @pre					The frame buffer must exist
	* @post					The depth texture is returned
	* @return				The depth texture
	*/
	Texture2D* GetDepthTexture(){ return depthTexture; };

	/**
	* @brief				Resize the texture
	* @pre					The frame buffer must exist
	* @post					The texture of the frame buffer is resizedd
	* @param w				The width of the texture
	* @param h				The height of the texture

	*/
	virtual void ResizeTexture(int w, int h) = 0;

protected:

	/**
	* @brief The width of the texture
	*/
	int width;

	/**
	* @brief The height of the texture
	*/
	int height;

	/**
	* @brief Whether the frame buffer should create a color attachement
	*/
	int numColorAttachments;

	std::vector<Texture2D*> colorAttachments;

	/**
	* @brief The depth texture
	*/
	Texture2D* depthTexture;

	/**
	* @brief The buffer id
	*/
	unsigned bufferID;
};
