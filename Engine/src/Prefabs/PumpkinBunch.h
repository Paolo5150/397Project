#pragma once
#include "..\GameObject\GameObject.h"
#include "..\Utils\AssetLoader.h"
#

class PumpkinBunch : public GameObject
{
public:
	enum STATE
	{
		SHOT,
		GROUND
	};

	PumpkinBunch();
	~PumpkinBunch();
	void Start() override;
	static unsigned totalPumpkinBunches;

private:
};