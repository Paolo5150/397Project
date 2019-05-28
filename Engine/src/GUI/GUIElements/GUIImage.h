#pragma once
#include  "GUIObject.h"
#include "..\..\Graphics\Texture2D.h"
#include "..\..\Core\Window.h"

/**
* @class GUIImage
* @brief Defines a GUI element for displaying textures

* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/

class GUIImage : public GUIObject
{
public:
	/**
	* @brief		Creates a GUI image
	*
	* @post			The GUIImage object is created
	* @param t		The texture to display
	* @param posX	The X position on the screen
	* @param posY	The Y position on the screen
	* @param sizeX	The width size of the image
	* @param sizeY	The height size of the image
	* @param isPercentage	Wether the details provided are percentage of the current window
	*/
	GUIImage(std::string uniqueName, Texture2D* t, float posX = 0, float posY = 0, float sizeX = 10, float sizeY = 10, bool isPercentage = false) : GUIObject(uniqueName){
		position.x = posX;
		position.y = posY;
		size.x = sizeX;
		size.y = sizeY;
		resizable = isPercentage;
		CalculateSizePosition();
		_imageID = t->GetID();
	};

	/**
	* @brief		Creates a GUI image
	*
	* @pre			The GUIImage object must exist
	* @post			The GUIImage object is destroyed
	*/
	~GUIImage(){};

	/**
	* @brief		Returns the image id
	*
	* @pre			The GUIImage object must exist
	* @post			The GUIImage id is returned
	* @return		The GUIImage id
	*/
	ImTextureID GetTextureID(){ return (ImTextureID)_imageID; }

	/**
	* @brief		Render the GUI object
	*/
	void RenderImGuiElement() override
	{
		ImGui::SetCursorPosX(pixelPosition.x);
		ImGui::SetCursorPosY(pixelPosition.y);
		ImGui::Image(GetTextureID(), ImVec2(pixelSize.x, pixelSize.y));
	}

private:

	/**
	* @brief		The image id
	*/
	unsigned _imageID;
};