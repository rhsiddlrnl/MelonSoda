#pragma once
#include "Actor.h"

class Monster : public Actor {
public:
	Monster(std::string monster_name, int monster_HP, int monster_MP, int monster_ATK, int monster_DEF, int event_index = (rand() % 4 + 1));
	void showMStat();
	int Event_index;
};

class Boss : public Monster {
public:
	using Monster::Monster;
};

//몬스터 선언부
extern const Monster slime;
extern const Monster king_slime;
extern const Monster waterrat;
extern const Monster chandelier;
