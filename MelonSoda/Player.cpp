#include "Player.h"
#include "SkillFactory.h"
#include "Monster.h"
#include "UIManager.h"

#include <iostream>
#include <algorithm>
#include <string>

// 스킬 맵 초기화
std::map<int, std::unique_ptr<Skill>> Player::skills = createSkillMap();

Player::Player()
{
	name = "defalut name";
	HP = 50;
	MP = 5;
	ATK = 10;
	DEF = 5;

	//참기 초기화
	concentration = 0;
	//최근 공격력 데미지 초기화
	lastDamage = 0;
	//1턴 동안 데미지 감소 상태 여부 초기화
	isReflecting = false;

	//전턴에 받은 데미지 임시저장
	hitDamage = 0;
}

void Player::Setname(std::string input)
{
	this -> name = input;
}

//void Player::showPStat() {
//	std::cout << "Name : " << name << std::endl;
//	std::cout << "HP : " << HP << std::endl;
//	std::cout << "MP : " << MP << std::endl;
//	std::cout << "ATK : " << ATK << std::endl;
//	std::cout << "DEF : " << DEF << std::endl;
//	std::cout << "concentration : " << concentration << std::endl;
//}

void Player::showInventory() {
	int num = 1;
	//과일하고 음료수 둘 다 하나이상 보유시에만 표시용
	if (!fruit_inventory.empty()) {
		G_UI->PrintLog("---과일 주머니---");
		for (const auto& item : fruit_inventory) {
			G_UI->PrintLog(num++ , " ", item.name);
		}
	}

	if (!drink_inventory.empty()) {
		G_UI->PrintLog("---마신 음료수---");
		for (const auto& item : drink_inventory) {
			G_UI->PrintLog(item.name);
		}
	}
}

void Player::addInventory(FRUIT fruit) {
	fruit_inventory.push_back(fruit);
	G_UI->PrintLog(fruit.name, "을(를) 획득했다!");

	HP += fruit.HP;
	MP += fruit.MP;
	ATK += fruit.ATK;
	DEF += fruit.DEF;

	G_UI->PrintLog(fruit.name , "을(를) 주머니에 넣었다. ");
	if (fruit.HP != 0) G_UI->PrintLog("체력이 ", fruit.HP, " 변화했다.");
	if (fruit.MP != 0) G_UI->PrintLog("마나가 ", fruit.MP, " 변화했다.");
	if (fruit.ATK != 0) G_UI->PrintLog("공격력이 ", fruit.ATK, " 변화했다.");
	if (fruit.DEF != 0) G_UI->PrintLog("방어력이 ", fruit.DEF, " 변화했다.");
}

void Player::useInventory(FRUIT fruit) {
	auto it = std::find(fruit_inventory.begin(), fruit_inventory.end(), fruit);
	if (it != fruit_inventory.end()) {
		G_UI->PrintLog(it->name , "의 효과가 사라졌다.");
		HP -= it->HP;
		MP -= it->MP;
		ATK -= it->ATK;
		DEF -= it->DEF;

		//if (fruit.HP != 0) std::cout << "체력이 " << it->HP << " ";
		//if (fruit.MP != 0) std::cout << "마나가 " << it->MP << " ";
		//if (fruit.ATK != 0) std::cout << "공격력이 " << it->ATK << " ";
		//if (fruit.DEF != 0) std::cout << "방어력이 " << it->DEF << " ";
		//std::cout << "감소했다." << std::endl;

		fruit_inventory.erase(it);
	}
	else {
		G_UI->PrintLog( "해당 아이템이 없습니다.");
	}
}

//연산자 중복이드래요~
void Player::blendFruit(FRUIT fruit1, FRUIT fruit2) {
	useInventory(fruit1);
	useInventory(fruit2);
	DRINK temp;
	temp = fruit1 + fruit2;
	addDrink(temp);
}

void Player::addDrink(DRINK drink)
{
	drink_inventory.push_back(drink);
	G_UI->PrintLog(drink.name , "을(를) 만들었다!");

	HP += drink.HP;
	MP += drink.MP;
	ATK += drink.ATK;
	DEF += drink.DEF;

	G_UI->PrintLog( drink.name, "을(를) 마셨다. ");
	if (drink.HP != 0) G_UI->PrintLog("체력이 ", drink.HP, " 증가했다.");
	if (drink.MP != 0) G_UI->PrintLog("마나가 ", drink.MP, " 증가했다.");
	if (drink.ATK != 0) G_UI->PrintLog("공격력이 ", drink.ATK , " 증가했다.");
	if (drink.DEF != 0) G_UI->PrintLog("방어력이 " , drink.DEF , " 증가했다.");

}

//참기 구현 함수
void Player::addConcentration() {
	concentration++;
	ATK += 2;
	DEF += 2;
	MP += 2;
	G_UI->PrintLog("참기를 모았다! 현재 참기: ", concentration);
	G_UI->PrintLog("공격력, 방어력, 마나가 각각 2씩 증가했다!");
}

int Player::useSkill(Monster& monster) {
	G_UI->PrintLog("");
	G_UI->PrintLog("[스킬 목록]");
	for (const auto& entry : skills) {
		int idx = entry.first;
		auto& skill = entry.second;
		/*G_UI->PrintLog(skill->name(), " - ", idx," , ", skill->name(), " - ", skill->description());*/
		G_UI->PrintLog(idx," - ",skill->name(), ",   - ", skill->description());

	}
	G_UI->PrintLog("스킬 번호를 입력하세요: ");
	int choice;
	std::cin >> choice;

	auto it = skills.find(choice);
	if (it != skills.end()) {
		G_UI->showLog();
		return it->second->execute(*this, monster);
	}
	else {
		G_UI->PrintLog("잘못된 선택입니다.");
	}
}