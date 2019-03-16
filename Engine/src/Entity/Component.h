#pragma once
#include <string>

class Component
{
public:
	Component(std::string name);
	~Component();

	void SetName(std::string name);
	std::string GetName() const;

private:
	std::string _name;
};

