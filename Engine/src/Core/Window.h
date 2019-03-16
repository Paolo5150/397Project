#pragma once
#include <GLFW\glfw3.h>
#include <string>



	class Window
	{
	public:
		friend class Core; //Core will initialize the window
		static Window& Instance();


		void Refresh();
		void Destroy();
		float GetAspectRatio();
		void UpdateEvents();
		void SetWindowSize(int w, int h);
		void GetWindowSize(int& w, int& h);
		void SetWindowTitle(std::string title);


	private:
		static void OnClose(GLFWwindow* win);
		static void OnResize(GLFWwindow* win, int w, int h);
		static void Initialize();
		static Window instance;

		GLFWwindow * window;
		Window();
		~Window();
	};
