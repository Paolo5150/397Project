#pragma once
#include  "GUIObject.h"
#include "..\..\Utils\FileUtils.h"
#include "GUIManager.h"

/**
* @class GUIProgressBar
* @brief Defines a GUI element for displaying a progress bar

* @author Paolo Ferri
* @version 01
* @date 11/05/2018
*
*
* @bug No known bugs.
*/
class GUIProgressBar : public GUIObject
{
public:
	/**
	* @brief		Creates a GUI text
	*
	* @post					The GUIText object is created
	* @param message		The text to display
	* @param posX			The X position on the screen
	* @param posY			The Y position on the screen
	* @param r				The red channel of the color
	* @param g				The green channel of the color
	* @param b				The blue channel of the color
	* @param isPercentage	Wether the details provided are percentage of the current window
	*/
	GUIProgressBar(std::string uniqueName,std::string message,float posX , float posY , float sizeX, float sizeY, bool isPercentage = false) : GUIObject(uniqueName){
		this->message = message;
		percentage = 1;
		int winX, winY;


		Window::Instance().GetWindowSize(winX, winY);
		if (!isPercentage)
		{
			winX = winY = 100;
		}
		size.x = sizeX * winX / 100;
		size.y = sizeY * winY / 100;
		position = glm::vec2(posX * winX / 100, posY * winY / 100);

	}

	/**
	* @brief		Destroy the GUIText
	*
	* @pre			The GUIText object must exist
	* @post			The GUIText object is destroyed
	*/
	~GUIProgressBar(){

	};

	std::string message;
	float percentage;

	void RenderImGuiElement() override
	{

		ImGui::SetCursorPosX(position.x);
		ImGui::SetCursorPosY(position.y);

		ImGui::ProgressBar(percentage, ImVec2(size.x, size.y),message.c_str());
	}

};