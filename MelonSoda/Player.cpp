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
	for (const auto& item : inventory) {
		std::cout << num++ << " " << item.name << "\n";
	}
}

void Player::addInventory(FRUIT fruit) {
	inventory.push_back(fruit);
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
	std::cout << "증가했다." << std::endl;
}

void Player::useInventory(FRUIT fruit) {
	auto it = std::find(inventory.begin(), inventory.end(), fruit);
	if (it != inventory.end()) {
		std::cout << it->name << "을(를) 사용했습니다. ";
		HP -= it->HP;
		MP -= it->MP;
		ATK -= it->ATK;
		DEF -= it->DEF;

		if (fruit.HP != 0) std::cout << "체력이 " << it->HP << " ";
		if (fruit.MP != 0) std::cout << "마나가 " << it->MP << " ";
		if (fruit.ATK != 0) std::cout << "공격력이 " << it->ATK << " ";
		if (fruit.DEF != 0) std::cout << "방어력이 " << it->DEF << " ";
		std::cout << "감소했다." << std::endl;

		inventory.erase(it);
	}
	else {
		std::cout << "해당 아이템이 없습니다." << std::endl;
	}
}

void Player::blendFruit(FRUIT fruit1, FRUIT fruit2) {
	useInventory(fruit1);
	useInventory(fruit2);
}
