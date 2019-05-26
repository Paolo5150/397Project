#pragma once
#include "Light.h"
#include "..\Core\Camera.h"
#include "..\Graphics\FrameBuffer.h"

/**
* @class DirectionalLight
* @brief Specialized class for a directional light object
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class DirectionalLight : public Light
{
public:
	/**
	* @brief						Create a new directional light object
	*
	* @post							The light object is created
	* @param castsShadows			Whether the light will cast shadows
	*/
	DirectionalLight(bool castsShadows = true);
	/**
	* @brief					Destroy the light object
	* @pre						The light object must exist
	* @post						The light object is destroyed
	*/
	~DirectionalLight();

	/**
	* @brief					The shadodw map 
	*/
	FrameBuffer* shadowMap;

	/**
	* @brief					Set whether the light will cast shadows
	* @pre						The light object must exist
	* @post						The light object aiblity to cast shadows is changed
	* @param enable				Whether the light will cast shadows
	*/
	void SetCastShadowEnable(bool enable);

	/**
	* @brief					Get whether the light will cast shadows
	* @pre						The light object must exist
	* @post						The light object aiblity to cast shadows is returned
	*/
	bool GetIsCastingShadow();

private:
	/**
	* @brief					Whether the light will cast shadows
	*/
	bool isCastingShadows;

};
