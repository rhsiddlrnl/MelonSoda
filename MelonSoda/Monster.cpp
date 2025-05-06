#include "Monster.h"
#include <iostream>

Monster::Monster(std::string monster_name, int monster_HP, int monster_MP, int monster_ATK, int monster_DEF, int event_index) {
	name = monster_name;
	HP = monster_HP;
	MP = monster_MP;
	ATK = monster_ATK;
	DEF = monster_DEF;
	Event_index = event_index;
}

void Monster::showMStat() {
	std::cout << "Name : " << name << std::endl;
	std::cout << "HP : " << HP << std::endl;
}

//몬스터 정의
const Monster slime("슬라임", 24, 0, 5, 3);
const Monster king_slime("킹슬라임", 37, 0, 8, 7);
const Monster chandelier("샹들리에", 61, 6, 13, 10);