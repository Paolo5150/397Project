#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"
#include "..\Components\HealthComponent.h"

class Hive : public GameObject
{
public:
	Hive();

	Hive(int maxSpiders);

	~Hive();

	void SetMaxSpiders(unsigned int maxSpiders);

	unsigned int GetMaxSpiders() const;

	void SetState(unsigned int index);

	unsigned int GetState() const;

	void Start() override;

	void Update() override;

	static unsigned int totalSpiders;

private:
	int _lastSpawnedSpider;
	unsigned int _currentState;
	unsigned int _maxSpiders;
	HealthComponent* healtthComponent;
};