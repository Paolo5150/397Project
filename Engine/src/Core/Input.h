#pragma once
#include <GLFW\glfw3.h>

static class Input
{
public:
	void Update();
	bool GetKeyPressed(GLFWwindow* window, int key);
	bool GetKeyDown(GLFWwindow* window, int key);
	bool GetKeyUp();
	void SetWindow(GLFWwindow* window);
	GLFWwindow* GetWindow() const;

private:
	GLFWwindow* _window;
};

