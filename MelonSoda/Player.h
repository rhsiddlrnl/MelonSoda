#pragma once
#include "Actor.h"
#include "Fruit.h"
#include "SkillFactory.h"
#include <vector>
#include <map>
#include <memory>
#include "Monster.h"

//플레이어는 기본액터 상속
//추가된 것: 인벤토리, 스토리 번호(스토리 순서대로 출력용), 생성자에 이름 매개변수로 받음(게임하는 사람이 입력함), 여러가지 함수들
class Player : public Actor {

public:
	std::vector<FRUIT> fruit_inventory;
	std::vector<DRINK> drink_inventory;
	int story_index;

	//플레이어 기본공격 시 참기
	int concentration;
	//최근 공격 데미지를 저장
	int lastDamage;
	//1턴 동안 데미지 감소 상태 여부
	bool isReflecting;
	//받은 데미지 저장
	int hitDamage;

	Player();

	void Setname(std::string input);

	//플레이어 스탯 보여주는 함수
	/*void showPStat();*/
	//플레이어 인벤토리 보여주는 함수
	void showInventory();
	//플레이어 인벤토리에 과일 추가하는 함수
	void addInventory(FRUIT fruit);
	//플레이어 인벤토리에서 과일 제거하는 함수
	void useInventory(FRUIT fruit);
	//BLEND!
	void blendFruit(FRUIT fruit1, FRUIT fruit2);
	//플레이어 인벤토리에 음료수 추가하는 함수
	void addDrink(DRINK drink);
	//플레이어 참기 함수
	void addConcentration();
	// 스킬 사용 함수
	int useSkill(Monster& monster);
	// 스킬 맵
	static std::map<int, std::unique_ptr<Skill>> skills;
};