#include "Player.h"
#include <iostream>
#include <algorithm>

Player::Player(std::string player_name) {
	name = player_name;
	HP = 20;
	MP = 10;
	ATK = 10;
	DEF = 5;
}

void Player::showPStat() {
	std::cout << "Name : " << name << std::endl;
	std::cout << "HP : " << HP << std::endl;
	std::cout << "MP : " << MP << std::endl;
	std::cout << "ATK : " << ATK << std::endl;
	std::cout << "DEF : " << DEF << std::endl;
}

void Player::showInventory() {
	int num = 1;
	if (!fruit_inventory.empty()) {
		std::cout << "---과일 주머니---" << std::endl;
		for (const auto& item : fruit_inventory) {
			std::cout << num++ << " " << item.name << std::endl;
		}
	}
	
	if (!drink_inventory.empty()) {
		std::cout << "---마신 음료수---" << std::endl;
		for (const auto& item : drink_inventory) {
			std::cout << item.name << std::endl;
		}
	}
}

void Player::addInventory(FRUIT fruit) {
	fruit_inventory.push_back(fruit);
	std::cout << fruit.name << "을(를) 획득했다!" << std::endl;
	HP += fruit.HP;
	MP += fruit.MP;
	ATK += fruit.ATK;
	DEF += fruit.DEF;

	std::cout << fruit.name << "을(를) 주머니에 넣었다. ";
	if (fruit.HP != 0) std::cout << "체력이 " << fruit.HP << " ";
	if (fruit.MP != 0) std::cout << "마나가 " << fruit.MP << " ";
	if (fruit.ATK != 0) std::cout << "공격력이 " << fruit.ATK << " ";
	if (fruit.DEF != 0) std::cout << "방어력이 " << fruit.DEF << " ";
	std::cout << "만큼 변화했다." << std::endl;
}

void Player::useInventory(FRUIT fruit) {
	auto it = std::find(fruit_inventory.begin(), fruit_inventory.end(), fruit);
	if (it != fruit_inventory.end()) {
		std::cout << it->name << "의 효과가 사라졌다." << std::endl;
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
		std::cout << "해당 아이템이 없습니다." << std::endl;
	}
}

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
	std::cout << drink.name << "을(를) 만들었다!" << std::endl;
	HP += drink.HP;
	MP += drink.MP;
	ATK += drink.ATK;
	DEF += drink.DEF;

	std::cout << drink.name << "을(를) 마셨다. ";
	if (drink.HP != 0) std::cout << "체력이 " << drink.HP << " ";
	if (drink.MP != 0) std::cout << "마나가 " << drink.MP << " ";
	if (drink.ATK != 0) std::cout << "공격력이 " << drink.ATK << " ";
	if (drink.DEF != 0) std::cout << "방어력이 " << drink.DEF << " ";
	std::cout << "증가했다!" << std::endl;
}
