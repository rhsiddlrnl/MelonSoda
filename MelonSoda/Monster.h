#pragma once
#include "Actor.h"
#include <map>
#include <string>

class Player;

class Monster : public Actor {

public:
	Monster(std::string monster_name, int monster_HP, int monster_MP, int monster_ATK, int monster_DEF, int event_index = (rand() % 4 + 1));
	void showMStat();

	int Event_index;

	int hitDamage;

	//가상함수 스택 가져올 용도
	virtual int Get_Stack();
};

class Boss : public Monster {
public:
	using Monster::Monster;
	// 미래 스택: 매 턴마다 +1
	int future = 0;

	// 플레이어에게 입힌 최근 데미지
	int lastDamage = 20;

	// 한 턴이 끝날 때마다 호출 HP +3, 미래 +1
	int regeneratePerTurn();
	// 뒤엎는 미래 스킬
	int overturnFuture();
	// 헤븐즈 도어 스킬
	int heavensDoor(Player& player);
	// 이계의 검 스킬
	int otherworldlyBlade(Player& player);

	//가상함수로 미래 스택 가져오기
	int Get_Stack();
};

extern Monster slime;
extern Monster king_slime;
extern Monster watterrat;
extern Monster chandelier;
extern Boss witch;

extern Monster zero;

inline std::map<int, Monster*> createMonsterMap() {
	std::map<int, Monster*> m;
	m[1] = &slime;
	m[2] = &king_slime;
	m[3] = &watterrat;
	m[4] = &chandelier;
	m[5] = &witch;
	return m;
}

extern std::map<int, Monster*> monsterMap;