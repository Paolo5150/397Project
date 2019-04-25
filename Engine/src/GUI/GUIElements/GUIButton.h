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
class GUIButton : public GUIObject
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
	GUIButton(std::string uniqueName, std::string message, std::function<void()> onclick,std::string fontName = "defaultFont", float sizeX = 50, float sizeY = 50, float posX = 0, float posY = 0, float r = 1, float g = 1, float b = 1, bool isPercentage = false) : GUIObject(uniqueName), _message(message){
		_color = glm::vec4(r, g, b, 1);
		int winX, winY;
		Window::Instance().GetWindowSize(winX, winY);
		if (!isPercentage)
		{
			winX = winY = 100;
		}

		position = glm::vec2(posX * winX / 100, posY * winY / 100);
		size.x = sizeX * winX / 100;
		size.y = sizeY * winY / 100;
		this->fontName = fontName;
		this->OnClick = onclick;


	}

	/**
	* @brief		Destroy the GUIText
	*
	* @pre			The GUIText object must exist
	* @post			The GUIText object is destroyed
	*/
	~GUIButton(){
		OnClick = nullptr;
	};

	std::function<void()> OnClick;

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
		
		//if (ImGui::ColorButton(_message.c_str(), ImVec4(_color.r, _color.g, _color.b, _color.a), ImGuiColorEditFlags_NoTooltip, ImVec2(size.x, size.y)))
		//	OnClick();
		
		if (ImGui::Button(_message.c_str(), ImVec2(size.x, size.y)))
		{
			GUIManager::Instance().buttonCallbacks.push_back(OnClick);

		}

		GUIManager::Instance().ResetFont();


	}

};