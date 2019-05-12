#pragma once

#include "..\GameObject\Component.h"

class HealthComponent : public Component
{
public:
	HealthComponent(float current, float max) : currentHealth(current), maxHealth(max), Component("HealthComponent") {

	}

	void AddToHealth(float amount) { 
		currentHealth = currentHealth + amount <= 0 ? 0 : currentHealth + amount;
	};
	bool IsDead() { return currentHealth <= 0; };
	float GetCurrentHealth() { return currentHealth; }
	void SetMaxHealth(float amount) { maxHealth = amount; }
	float GetHealthMaxRatio() { return currentHealth / maxHealth; }
	float GetMaxHealth() { return maxHealth; }

private:
	float currentHealth;
	float maxHealth;

};