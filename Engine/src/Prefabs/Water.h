#pragma once
#include "..\GameObject\Component.h"
#include "..\Components\MeshRenderer.h"

#include "..\Graphics\Layers.h"
#include "..\Graphics\FrameBuffer.h"
#include "..\Core\CameraPerspective.h"


/**
* @class Water
* @brief Premade gameobject for a water object
*
*
* @author Paolo Ferri
* @version 01
* @date 05/03/2019
*
*
* @bug No known bugs.
*/
class Water : public GameObject
{
public:

	/**
	* @brief						Create a new water object 
	*
	* @post							The water object is created with the specified parameters
	*
	* @param		normalMap		The normal map of the water
	* @param		distortion		The distortion map of the water
	*/
	Water(Texture2D* normalMap, Texture2D* distortion);

	/**
	* @brief						Create a new water object
	*
	* @post							The water object is created with the specified parameters
	*
	*/
	Water();

	/**
	* @brief						Destroy the water object
	* @pre							The object must exist
	* @post							The water object is destroyed
	*/
	~Water();

	/**
	* @brief						Update the reflection and refraction textures
	* @pre							The object must exist
	* @post							The textures are updated
	*/
	void Update() override;

	/**
	* @brief						The refraction texture
	*/
	FrameBuffer* refractionBuffer;

	/**
	* @brief						The reflection texture
	*/
	FrameBuffer* reflectionBuffer;

	/**
	* @brief						Reference to the scene main camera
	*/
	CameraPerspective* mainCamera;

	/**
	* @brief		Callback called right before the Render method
	*
	* @pre			The render method has not been called
	* @post			The method is called before Render
	*
	* @param cam	The camera used to render the object
	* @param currentShader	The shader used to render the object
	*/
	void OnPreRender(Camera& camera, Shader* currentShader = nullptr) ;

	void OnPostRender(Camera& camera, Shader* currentShader = nullptr);


	/**
	* @brief		The mesh renderer component
	*/
	MeshRenderer* meshRenderer;
private:

	/**
	* @brief		Callback invoked when the screen is resized
	*/
	bool ResizeFrameBuffers(Event* e);

	/**
	* @brief		The camera used to render the scene on the textures
	*/
	CameraPerspective* waterCamera;


	/**
	* @brief		The material used by the water object
	*/
	Material* material;

	/**
	* @brief		Timer variable sent to the shader to move the textures
	*/
	float timer;

	/**
	* @brief		Initialize water object
	*/
	void Initialize(Texture2D* normalMap = nullptr, Texture2D* distortion = nullptr);



};

