#pragma once
#include <GLFW\glfw3.h>
#include "Logger.h"

/**
* @class Input
* @brief Allows for retreiving of GLFW keystates
*
*
*Contains functions to determine the current state of keys
*
* @author Dylan Green
* @version 01
* @date 15/03/2018
*
*
* @bug No known bugs.
*/
static class Input
{
public:
//---- Public Member Functions ----//
	//-- GLFW --//
	/**
	* @brief		Initialises the glfwSetKeyCallback and keys array, and optionally the glfwSetErrorCallback
	*
	* @pre			GLFW must be initialised
	* @post			glfwSetKeyCallback is intialised in reference to the window input
	*
	* @param		window		GLFWwindow pointer to reference for the KeyCallback
	* @param		logErrors	Enables glfwSetErrorCallback, which logs glfw errors to the Logger
	*/
	static void Init(GLFWwindow* window, bool logErrors = false);

	/**
	* @brief		Facade that calls glfwPollEvents(), this should be called regularly
	*/
	static void Update();

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-- Accessors --//
	/**
	* @brief		Returns whether the key specified equals GLFW_PRESS
	*
	* @pre			The GameObject must exist.
	* @post			The true or false, depending on the value stored in keys[key] will be retreived
	*
	* @return		true if keys[key] equals GLFW_PRESS, else false
	*/
	static bool GetKeyPressed(int key);

	/**
	* @brief		Returns whether the key specified equals GLFW_REPEAT
	*
	* @pre			The GameObject must exist.
	* @post			The true or false, depending on the value stored in keys[key] will be retreived
	*
	* @return		true if keys[key] equals GLFW_REPEAT, else false
	*/
	static bool GetKeyDown(int key);

	/**
	* @brief		Returns whether the key specified equals GLFW_RELEASE
	*
	* @pre			The GameObject must exist.
	* @post			The true or false, depending on the value stored in keys[key] will be retreived
	*
	* @return		true if keys[key] equals GLFW_RELEASE, else false
	*/
	static bool GetKeyUp(int key);

private:
	static int keys[400]; //Stores the last updated value of the keys

//---- Private Member Functions ----//
	//-- GLFW Callbacks --//
	/**
	* @brief		Callback for glfwSetKeyCallback
	*/
	static void Key_Callback(GLFWwindow* window, int, int, int, int);

	/**
	* @brief		Callback for glfwSetErrorCallback
	*/
	static void Error_Callback(int error, const char* description);
};

