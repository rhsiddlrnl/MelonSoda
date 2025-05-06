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
		std::cout << "---���� �ָӴ�---" << std::endl;
		for (const auto& item : fruit_inventory) {
			std::cout << num++ << " " << item.name << std::endl;
		}
	}
	
	if (!drink_inventory.empty()) {
		std::cout << "---���� �����---" << std::endl;
		for (const auto& item : drink_inventory) {
			std::cout << item.name << std::endl;
		}
	}
}

void Player::addInventory(FRUIT fruit) {
	fruit_inventory.push_back(fruit);
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
	auto it = std::find(fruit_inventory.begin(), fruit_inventory.end(), fruit);
	if (it != fruit_inventory.end()) {
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

		fruit_inventory.erase(it);
	}
	else {
		std::cout << "�ش� �������� �����ϴ�." << std::endl;
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
	std::cout << drink.name << "��(��) �������!" << std::endl;

	HP += drink.HP;
	MP += drink.MP;
	ATK += drink.ATK;
	DEF += drink.DEF;

	std::cout << drink.name << "��(��) ���̴�. ";
	if (drink.HP != 0) std::cout << "ü���� " << drink.HP << " ";
	if (drink.MP != 0) std::cout << "������ " << drink.MP << " ";
	if (drink.ATK != 0) std::cout << "���ݷ��� " << drink.ATK << " ";
	if (drink.DEF != 0) std::cout << "������ " << drink.DEF << " ";
	std::cout << "�����ߴ�." << std::endl;
}
