#include "Player.h"
#include <iostream>
#include <algorithm>
#include "Monster.h"

Player::Player(std::string player_name) {
	name = player_name;
	HP = 100;
	MP = 10;
	ATK = 10;
	DEF = 5;

	//���� �ʱ�ȭ
	concentration = 0;
	//�ֱ� ���ݷ� ������ �ʱ�ȭ
	lastDamage = 0;
	//1�� ���� ������ ���� ���� ���� �ʱ�ȭ
	isReflecting = false;
}

void Player::showPStat() {
	std::cout << "Name : " << name << std::endl;
	std::cout << "HP : " << HP << std::endl;
	std::cout << "MP : " << MP << std::endl;
	std::cout << "ATK : " << ATK << std::endl;
	std::cout << "DEF : " << DEF << std::endl;
	std::cout << "concentration : " << concentration << std::endl;
}

void Player::showInventory() {
	int num = 1;
	//�����ϰ� ����� �� �� �ϳ��̻� �����ÿ��� ǥ�ÿ�
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
	std::cout << "��ŭ ��ȭ�ߴ�." << std::endl;
}

void Player::useInventory(FRUIT fruit) {
	auto it = std::find(fruit_inventory.begin(), fruit_inventory.end(), fruit);
	if (it != fruit_inventory.end()) {
		std::cout << it->name << "�� ȿ���� �������." << std::endl;
		HP -= it->HP;
		MP -= it->MP;
		ATK -= it->ATK;
		DEF -= it->DEF;

		//if (fruit.HP != 0) std::cout << "ü���� " << it->HP << " ";
		//if (fruit.MP != 0) std::cout << "������ " << it->MP << " ";
		//if (fruit.ATK != 0) std::cout << "���ݷ��� " << it->ATK << " ";
		//if (fruit.DEF != 0) std::cout << "������ " << it->DEF << " ";
		//std::cout << "�����ߴ�." << std::endl;

		fruit_inventory.erase(it);
	}
	else {
		std::cout << "�ش� �������� �����ϴ�." << std::endl;
	}
}

//������ �ߺ��̵巡��~
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
	std::cout << "�����ߴ�!" << std::endl;
}

//���� ���� �Լ�
void Player::addConcentration() {
	concentration++;
	ATK += 2;
	DEF += 2;
	MP += 2;
	std::cout << "���⸦ ��Ҵ�! ���� ����: " << concentration << std::endl;
	std::cout << "���ݷ�, ����, ������ ���� 2�� �����ߴ�!" << std::endl;
}

//�÷��̾� ��ų ��� �Լ�
void Player::useSkill(Monster& monster) {
	int skillChoice;
	std::cout << "\n[��ų ���]\n";
	std::cout << "1. �ҵ� ���� (���� 3, MP 4)\n";
	std::cout << "   - �ֱ� ������ 1.4�� ���� + ������ ���ݸ�ŭ HP ȸ��\n";

	std::cout << "2. ���� (MP 3)\n";
	std::cout << "   - �ֱ� ������ 1.3�� ���� + ���� +1\n";

	std::cout << "3. ƨ�ܳ��� (MP 4)\n";
	std::cout << "   - 1�� ���� �޴� ������ 30% ���� + ���� +1\n";

	std::cout << "4. ������ (���� 2, MP 4)\n";
	std::cout << "   - (���� HP �� 0.1) �� ���� ���� ���ø�ŭ ����\n";

	std::cout << "��ų ��ȣ�� �Է��ϼ���: ";
	std::cin >> skillChoice;

	switch (skillChoice) {
	case 1:
		swordOrder(monster);
		break;
	case 2:
		slash(monster);
		break;
	case 3:
		reflect();
		break;
	case 4:
		release(monster);
		break;
	default:
		std::cout << "�߸��� �����Դϴ�.\n";
		break;
	}
}

//�÷��̾� �ҵ���� ��ų �Լ�
void Player::swordOrder(Monster& monster) {
	if (concentration < 3) {
		std::cout << "���Ⱑ �����մϴ�. (�ʿ�: 3, ����: " << concentration << ")\n";
		return;
	}
	if (MP < 4) {
		std::cout << "������ �����մϴ�. (�ʿ�: 4, ����: " << MP << ")\n";
		return;
	}

	MP -= 4;
	concentration -= 3;

	int damage = static_cast<int>(lastDamage * 1.4);
	monster.HP -= damage;
	int heal = damage / 2;
	HP += heal;

	std::cout << "\n[�ҵ� ���� ��ų ���]\n";
	std::cout << "- " << monster.name << "���� " << damage << " �������� ������.\n";
	std::cout << "- ������ ����(" << heal << ") ��ŭ HP�� ȸ���ߴ�.\n";
}

//�÷��̾� ���� ��ų �Լ�
void Player::slash(Monster& monster) {
	if (MP < 3) {
		std::cout << "������ �����մϴ�. (�ʿ�: 3, ����: " << MP << ")\n";
		return;
	}

	MP -= 3;

	//�⺻ ���� ���� �� �ʱ� ���ݷ� ���
	int baseDamage = (lastDamage > 0) ? lastDamage : ATK;
	int estimated = static_cast<int>(baseDamage * 1.3);

	// ���� ������ ���Ŀ� ���� ó��
	int att = estimated;
	int def = monster.DEF;
	int damage = (att * 100) / (def + 100);

	monster.HP -= damage;

	// ���� 1 ���� �� �ɷ�ġ ���
	concentration++;
	ATK += 2;
	DEF += 2;
	MP += 2;

	std::cout << "\n[���� ��ų ���]\n";
	std::cout << "- " << monster.name << "���� " << damage << " �������� ������.\n";
	if (lastDamage == 0) {
		std::cout << "- �ֱ� ���� ��� ���� �� �⺻ ���ݷ�(" << baseDamage << ") �������� ���\n";
	}
	std::cout << "- ���⸦ ��Ҵ�! ���� ����: " << concentration << ", ���ݷ�, ����, ������ ���� 2�� �����ߴ�!\n";
}

//�÷��̾� ƨ�ܳ��� ��ų
void Player::reflect() {
	if (MP < 4) {
		std::cout << "������ �����մϴ�. (�ʿ�: 4, ����: " << MP << ")\n";
		return;
	}

	MP -= 4;
	concentration++;
	ATK += 2;
	DEF += 2;
	MP += 2;

	isReflecting = true;  //�� �� ���� ������ ���� ����

	std::cout << "\n[ƨ�ܳ��� ��ų ���]\n";
	std::cout << "- ������ ���� ���� ���ذ� 30% ���ҵ˴ϴ�.\n";
	std::cout << "- ���� ���� +1 (����: " << concentration << "), ATK/DEF/MP +2\n";
}

//�÷��̾� ������ ��ų
void Player::release(Monster& monster) {
	if (concentration < 2) {
		std::cout << "���Ⱑ �����մϴ�. (�ʿ�: 2, ����: " << concentration << ")\n";
		return;
	}
	if (MP < 4) {
		std::cout << "������ �����մϴ�. (�ʿ�: 4, ����: " << MP << ")\n";
		return;
	}

	MP -= 4;

	// ((�÷��̾��� ���� hp) x 0.1) x (���� ����)
	int damage = static_cast<int>((HP * 0.1) * concentration);
	monster.HP -= damage;

	// ���� 2 �Ҹ�
	concentration -= 2;

	std::cout << "\n[������ ��ų ���]\n";
	std::cout << "- ���� HP�� 10% �� ���� ������ ���ط� ��ȯ!\n";
	std::cout << "- " << monster.name << "���� " << damage << " �������� ������.\n";
	std::cout << "- ���� ���� 2�� �Ҹ�Ǿ����ϴ�. (����: " << concentration << ")\n";
}