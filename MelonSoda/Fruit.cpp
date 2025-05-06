#include "Fruit.h"

FRUIT::FRUIT(std::string fruit_name, int fruit_HP, int fruit_MP, int fruit_ATK, int fruit_DEF, int fruit_index) {
	name = fruit_name;
	HP = fruit_HP;
	MP = fruit_MP;
	ATK = fruit_ATK;
	DEF = fruit_DEF;
	Index = fruit_index;
}

bool FRUIT::operator==(const FRUIT& other) const {
	return name == other.name && Index == other.Index;
}

//과일("이름", 체력, 마나, 공격력, 방어력, 블렌드용번호) 블렌드용 번호는 1 2 4 8 16 32 64 128...이런식으로 부여할 것
const FRUIT orange("오렌지", 0, 0, 0, 0, 1);
const FRUIT apple("사과",0, 0, 0, 0, 2);
const FRUIT grapefruit("자몽", 0, 0, 0, 0, 4);
const FRUIT grape("포도", 0, 0, 0, 0, 8);
const FRUIT avocado("아보카도", 0, 0, 0, 0, 16);
const FRUIT watermelon("수박", 0, 0, 0, 0, 32);

//음료수("이름", 체력, 마나, 공격력, 방어력, 블렌드용번호) 블렌드용 번호는 과일 블렌드용번호 2개합으로 3 5 6 9 10 12...이런식으로 부여할 것