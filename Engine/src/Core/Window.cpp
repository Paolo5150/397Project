
#include "Window.h"
#include "Logger.h"
#include "..\Event\EventDispatcher.h"
#include "..\Event\WindowEvents.h"

Window Window::instance;

Window& Window::Instance()
{

	return instance;
}

void Window::Initialize()
{

	//Set up environment
	//Glew init MUST be called after creating the context (the window)
	if (!glfwInit())
	{
		Logger::LogError("GLFW failed to initialize");
	}


	glfwWindowHint(GLFW_DOUBLEBUFFER, true);
	instance.window = glfwCreateWindow(800, 600, "", NULL, NULL);
	glfwMakeContextCurrent(instance.window);
	
	glfwSetWindowCloseCallback(instance.window, OnClose);
	glfwSetWindowSizeCallback(instance.window, OnResize);
	glfwSwapInterval(0);
}

Window::Window()
{
}

Window::~Window()
{
	Destroy();
}



void Window::UpdateEvents()
{
	glfwPollEvents();
}

float Window::GetAspectRatio()
{
	int w, h;
	GetWindowSize(w, h);
	return (float)w / h;
}

void Window::SetWindowSize(int w, int h)
{
	glfwSetWindowSize(this->window,w, h);

}
void Window::GetWindowSize(int& w, int& h)
{
	glfwGetWindowSize(this->window, &w, &h);
}

void Window::SetWindowTitle(std::string title)
{
	glfwSetWindowTitle(this->window, title.c_str());
}

void Window::Refresh()
{
	glfwSwapBuffers(window);

}

void Window::Destroy()
{
	glfwSetWindowShouldClose(window, true);
	glfwDestroyWindow(window);
	window = NULL;
}

void Window::OnClose(GLFWwindow* win)
{
	glfwSetWindowShouldClose(win, false); //Prevent window from closing	
	EventDispatcher::Instance().DispatchEvent(new WindowCloseEvent());
}



void Window::OnResize(GLFWwindow* win, int w, int h)
{

	EventDispatcher::Instance().DispatchEvent(new WindowResizeEvent(w,h));
}