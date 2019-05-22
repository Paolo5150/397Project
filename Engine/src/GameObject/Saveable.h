#include <iostream>
#include <list>

class Saveable
{
public:
	Saveable();
	~Saveable();
	virtual std::string Save() = 0;

	static std::list<Saveable*> GetSaveableObects();

private:
	static std::list<Saveable*> _saveableObjects;
};

