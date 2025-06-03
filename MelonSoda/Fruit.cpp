#include "Fruit.h"
#include "UIManager.h"

#include <iostream>
#include <map>

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
const FRUIT orange("오렌지", 1, 0, 2, 0, 1);
const FRUIT apple("사과",0, 2, 0, 2, 2);
const FRUIT grapefruit("자몽", 0, 0, 3, -1, 4);
const FRUIT grape("포도", 3, 0, -2, 0, 8);
const FRUIT avocado("아보카도", 0, -2, 0, 2, 16);
const FRUIT watermelon("수박", -3, 0, 2, -1, 32);

//음료수("이름", 체력, 마나, 공격력, 방어력, 블렌드용번호) 블렌드용 번호는 과일 블렌드용번호 2개합으로 부여할 것
const DRINK puresour("퓨어사워", 0, 0, 4, 4, 1+2);
const DRINK twoblood("투 블로드", 5, 0, 6, 0, 1+4);
const DRINK darklip("다크 립", 3, 0, 0, 4, 1+8);
const DRINK unlock("언록", 0, 0, 0, 7, 1+16);
const DRINK deepjune("딥 쥰", 0, 5, 0, 4, 2+4);
const DRINK heaven("헤븐", 0, 2, 3, 3, 2+8);
const DRINK mellowyellow("멜로우 옐로우", 0, 0, 7, 0, 2+32);
const DRINK darkseed("다크시드", 4, 0, 6, 0, 4+8);
const DRINK oceanmood("오션무드", 3, 0, 0, 5, 4+16);
const DRINK sourshower("사워샤워", 5, 0, 0, 3, 8+16);
const DRINK squished("스퀴시드", 3, 3, 5, 0, 8+32);
const DRINK clearred("클리어 레드", 6, 3, 5, 0, 16+32);
const DRINK unluckymelon("언럭키멜론", 5, 5, 5, 5, 32+32);

std::map<int, DRINK> drinkMap = {
    {1 + 2, puresour},
    {1 + 4, twoblood},
    {1 + 8, darklip},
    {1 + 16, unlock},
    {2 + 4, deepjune},
    {2 + 8, heaven},
    {2 + 32, mellowyellow},
    {4 + 8, darkseed},
    {4 + 16, oceanmood},
    {8 + 16, sourshower},
    {8 + 32, squished},
    {16 + 32, clearred},
    {32 + 32, unluckymelon}
};

DRINK operator+(const FRUIT& fruit1, const FRUIT& fruit2)
{
    int blendIndex = fruit1.Index + fruit2.Index;
    if (drinkMap.count(blendIndex)) {
        return drinkMap[blendIndex];
    }
    else {
        G_UI->PrintLog( "흠...더 나은 조합법이 있지 않았을까?");
        return DRINK("그냥저냥 음료수", 0, 0, 2, 2);
    }
}
