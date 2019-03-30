#pragma once
#include <string>
#include "..\Core\Logger.h"

class Asset
{
public:
	Asset(){};
	virtual ~Asset(){ /*Logger::LogInfo("Delete asset", name);*/ };
	std::string name;
	bool preserve;

};