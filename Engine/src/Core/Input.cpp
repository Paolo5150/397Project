#include "..\pch.h"
#include "Input.h"

//-----Public-----//
void Input::Init(GLFWwindow* window, bool logErrors)
{
	glfwSetKeyCallback(window, Key_Callback);

	if (logErrors == true)
	{
		glfwSetErrorCallback(Error_Callback);
	}

	for (int i = 0; i < 400; i++)
	{
		keys[i] = 0;
	}
}

void Input::Update()
{
	glfwPollEvents();
}

bool Input::GetKeyPressed(int key)
{
	if (keys[key] == GLFW_PRESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Input::GetKeyDown(int key)
{
	if (keys[key] == GLFW_REPEAT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Input::GetKeyUp(int key)
{
	if (keys[key] == GLFW_RELEASE)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//-----Private-----//
int Input::keys[400];

void Input::Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < 400)
	{
		keys[key] = action;
	}
	else
	{
		Logger::LogError("Key_Callback went out of range!");
	}
}

void Input::Error_Callback(int error, const char* description)
{
	Logger::LogError(description);
}