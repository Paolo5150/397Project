#pragma once
#include<string>

#include "..\GameObject\GameObject.h"
#include "..\GameObject\Saveable.h"
#include "..\Utils\AssetLoader.h"
#include "..\Components\HealthComponent.h"

class Hive : public GameObject, public Saveable
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

	std::string Save() override;
	
	static unsigned int totalHives;
	HealthComponent* healthComponent;
private:
	float colorTimer;
	bool redFlashing;
	bool canSpawnSpiders;
	int _lastSpawnedSpider;
	unsigned int _currentState;
	unsigned int _maxSpiders;
};