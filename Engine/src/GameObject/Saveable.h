#pragma once
#include <string>
#include <list>

/**
* @class Saveable
* @brief Class for objects that can be saved
*
*
* @author Dylan Green
* @version 01
* @date 27/05/2019
*
*
* @bug No known bugs.
*/
class Saveable
{
public:
	/**
	* @brief		Constructor
	* @pre			The Saveable object does not exist
	* @post			The Saveable object is created
	*/
	Saveable();

	/**
	* @brief		Destructor
	* @pre			The Saveable object must exist
	* @post			The Saveable object is destroyed
	*/
	~Saveable();

	/**
	* @brief		Virtual method for saving the class
	*
	* @pre			The Saveable object must exist
	*
	* @return		String with the data to save
	*/
	virtual std::string Save() = 0;

	/**
	* @brief		Returns the list of saveable objects
	*
	* @pre			The Saveable object must exist
	*
	* @return		the list of saveable objects
	*/
	static std::list<Saveable*>& GetSaveableObects();

private:
	/**
	* @brief		List of all saveable objects
	*/
	static std::list<Saveable*> _saveableObjects;
};

