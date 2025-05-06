#pragma once
#include "Actor.h"

class FRUIT : public Actor {
public:
	int Index;

	FRUIT(std::string fruit_name = " ", int fruit_HP = 0, int fruit_MP = 0, int fruit_ATK = 0, int fruit_DEF = 0, int fruit_index = 0);
	bool operator==(const FRUIT& other) const;
};

class DRINK : public FRUIT {
public:
	using FRUIT::FRUIT;
};

DRINK operator+(const FRUIT& fruit1, const FRUIT& fruit2);

//과일 선언 extern const 붙이기
extern const FRUIT orange;
extern const FRUIT apple;
extern const FRUIT grapefruit;
extern const FRUIT grape;
extern const FRUIT avocado;
extern const FRUIT watermelon;

//음료수 선언도 마찬가지
extern const DRINK puresour;
extern const DRINK twoblood;
extern const DRINK darklip;
extern const DRINK unlock;
extern const DRINK deepjune;
extern const DRINK heaven;
extern const DRINK mellowyellow;
extern const DRINK darkseed;
extern const DRINK oceanmood;
extern const DRINK sourshower;
extern const DRINK squished;
extern const DRINK clearred;
extern const DRINK unluckymelon;