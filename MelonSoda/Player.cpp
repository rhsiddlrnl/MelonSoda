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
	std::cout << fruit.name << "��(��) ȹ���ߴ�!" << std::endl;

	HP += fruit.HP;
	MP += fruit.MP;
	ATK += fruit.ATK;
	DEF += fruit.DEF;

	std::cout << fruit.name << "��(��) �ָӴϿ� �־���. ";
	if (fruit.HP != 0) std::cout << "ü���� " << fruit.HP << " ";
	if (fruit.MP != 0) std::cout << "������ " << fruit.MP << " ";
	if (fruit.ATK != 0) std::cout << "���ݷ��� " << fruit.ATK << " ";
	if (fruit.DEF != 0) std::cout << "������ " << fruit.DEF << " ";
	std::cout << "�����ߴ�." << std::endl;
}

void Player::useInventory(FRUIT fruit) {
	auto it = std::find(inventory.begin(), inventory.end(), fruit);
	if (it != inventory.end()) {
		std::cout << it->name << "��(��) ����߽��ϴ�. ";
		HP -= it->HP;
		MP -= it->MP;
		ATK -= it->ATK;
		DEF -= it->DEF;

		if (fruit.HP != 0) std::cout << "ü���� " << it->HP << " ";
		if (fruit.MP != 0) std::cout << "������ " << it->MP << " ";
		if (fruit.ATK != 0) std::cout << "���ݷ��� " << it->ATK << " ";
		if (fruit.DEF != 0) std::cout << "������ " << it->DEF << " ";
		std::cout << "�����ߴ�." << std::endl;

		inventory.erase(it);
	}
	else {
		std::cout << "�ش� �������� �����ϴ�." << std::endl;
	}
}

void Player::blendFruit(FRUIT fruit1, FRUIT fruit2) {
	useInventory(fruit1);
	useInventory(fruit2);
}
