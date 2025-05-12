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

//���� ���� ������ ���� �������׸� �������� �Ű����� �߰��ϱ� ex) const Montser preBoss("���� ���� ����", 50, 4, 5, 1, 3, 5);
const Monster slime("������", 24, 0, 5, 3);
const Monster king_slime("ŷ������", 37, 0, 8, 7);
const Monster waterrat("���ͷ�", 49, 0, 11, 11);
const Monster chandelier("���鸮��", 61, 6, 13, 10);

std::map<int, Monster> monsterMap = {
	  {1, slime},
	  {2, king_slime},
	  {3, waterrat},
	  {5, chandelier}
};