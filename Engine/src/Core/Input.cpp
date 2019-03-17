#include "..\pch.h"
#include "Input.h"


void Input::Update()
{
	glfwPollEvents();
}

bool Input::GetKeyPressed()
{

}

bool Input::GetKeyDown()
{

}

bool Input::GetKeyUp()
{

}

void Input::SetWindow(GLFWwindow* window)
{
	_window = window;
}

GLFWwindow* Input::GetWindow() const
{
	return _window;
}