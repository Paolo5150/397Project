#pragma once
#include  "GUIObject.h"
#include "..\..\Utils\FileUtils.h"
#include "GUIManager.h"

/**
* @class GUIProgressBar
* @brief Defines a GUI element for displaying a progress bar

* @author Paolo Ferri
* @version 01
* @date 11/05/2019
*
*
* @bug No known bugs.
*/
class GUIProgressBar : public GUIObject
{
public:
	/**
	* @brief		Creates a GUIProgressBar
	*
	* @post					The GUIProgressBar object is created
	* @param message		The text to display
	* @param posX			The X position on the screen
	* @param posY			The Y position on the screen
	* @param sizeX			The width of the progress bar
	* @param sizeY			The height of the progress bar
	* @param isPercentage	Wether the details provided are percentage of the current window
	*/
	GUIProgressBar(std::string uniqueName,std::string message,float posX , float posY , float sizeX, float sizeY, bool isPercentage = false) : GUIObject(uniqueName){
		this->message = message;
		position.x = posX;
		position.y = posY;
		size.x = sizeX;
		size.y = sizeY;
		resizable = isPercentage;
		CalculateSizePosition();

	}

	/**
	* @brief		Destroy the GUIProgressBar
	*
	* @pre			The GUIProgressBar object must exist
	* @post			The GUIProgressBar object is destroyed
	*/
	~GUIProgressBar(){

	};

	/**
	* @brief		Message to be displayed on the bar
	*/
	std::string message;

	/**
	* @brief		The value / max value ratio
	*/
	float percentage;

	/**
	* @brief		Render the GUI object
	*/
	void RenderImGuiElement() override
	{

		ImGui::SetCursorPosX(pixelPosition.x);
		ImGui::SetCursorPosY(pixelPosition.y);		
		ImGui::ProgressBar(percentage, ImVec2(pixelSize.x, pixelSize.y), message.c_str());
		
	}

};