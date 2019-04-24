#pragma once
#include  "GUIObject.h"
#include "..\..\Utils\FileUtils.h"
#include "GUIManager.h"

/**
* @class GUIText
* @brief Defines a GUI element for displaying text

* @author Paolo Ferri
* @version 01
* @date 15/03/2018
*
*
* @bug No known bugs.
*/
class GUIText : public GUIObject
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
	GUIText(std::string uniqueName, std::string message, std::string fontName = "defaultFont", float posX = 0, float posY = 0, float r = 1, float g = 1, float b = 1, bool isPercentage = false) : GUIObject(uniqueName), _message(message){
		_color = glm::vec4(r, g, b, 1);
		int winX, winY;
		Window::Instance().GetWindowSize(winX, winY);
		if (!isPercentage)
		{
			winX = winY = 100;
		}

		position = glm::vec2(posX * winX / 100, posY * winY / 100);

		this->fontName = fontName;
	
	}

	/**
	* @brief		Destroy the GUIText
	*
	* @pre			The GUIText object must exist
	* @post			The GUIText object is destroyed
	*/
	~GUIText(){

	};
	
	/**
	* @brief		The message to be displayed
	*/
	std::string _message;

	/**
	* @brief		The mtext color
	*/
	glm::vec4 _color;

	std::string fontName;

	void RenderImGuiElement() override
	{
		ImGui::SetCursorPosX(position.x);
		ImGui::SetCursorPosY(position.y);	

		GUIManager::Instance().SelectFont(fontName);

		ImGui::TextColored(ImVec4(_color.x,_color.y,_color.z,_color.w),_message.c_str());
		GUIManager::Instance().ResetFont();


	}

};