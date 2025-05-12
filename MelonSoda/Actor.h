#pragma once
#include <string>

class Actor {
public:
	std::string name;
	int HP;
	int MP;
	int ATK;
	int DEF;

	virtual ~Actor() {}
};