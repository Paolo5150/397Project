#pragma once

#include "..\GameObject\Component.h"


/**
* @class HealthComponent
* @brief Specialized class for a health component
*
*
* @author Paolo Ferri
* @version 01
* @date 14/05/2019
*
* @bug No known bugs.
*/
class HealthComponent : public Component
{
public:
	/**
	* @brief		Constructor
	* @pre			The Component does not exist
	* @post			The Component is created
	* @param current The initial value of health
	* @param max	 The max value of health
	*/
	HealthComponent(float current, float max) : currentHealth(current), maxHealth(max), Component("HealthComponent") {

	}

	/**
	* @brief			Add value to current health
	* @pre				The Component must exist
	* @post				The health is updated
	* @param amount		The amount to be added to current health
	*/
	void AddToHealth(float amount) { 
		currentHealth = currentHealth + amount <= 0 ? 0 : currentHealth + amount;
	};

	/**
	* @return true if the current health is <= 0
	*/
	bool IsDead() { return currentHealth <= 0; };

	/**
	* @return the current health value
	*/
	float GetCurrentHealth() { return currentHealth; }

	/**
	* @brief Set the maximum health
	* @param amoung The new max health
	*/
	void SetMaxHealth(float amount) { maxHealth = amount; }

	/**
	* @return The ratio between current health and max health
	*/
	float GetHealthMaxRatio() { return currentHealth / maxHealth; }

	/**
	* @return The max health
	*/
	float GetMaxHealth() { return maxHealth; }

private:
	/**
	* @return Current health
	*/
	float currentHealth;

	/**
	* @return Maximum health
	*/
	float maxHealth;

};