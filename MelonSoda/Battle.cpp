#include "Battle.h"

void Battle(Player& player, Monster& monster)
{
	std::cout << monster.name << "��(��) ��Ÿ����!" << std::endl;
	while ((player.HP > 0) && (monster.HP > 0)) {
		std::cout << player.name << "�� ����!" << std::endl;
		int playerSelect = 0;
		int monsterSelect = 0;		//���� ai ������
		while (1) {
			std::cout << "������ �ұ�?" << std::endl;
			std::cout << "1. ���� 2. ��ų 3. ����Ȯ��" << std::endl;
			std::cin >> playerSelect;
			if (playerSelect == 1) {
				monster.HP -= dmg(player, monster);
				break;
			}
			else if (playerSelect == 2) {
				std::cout << "��ų�� ���� �̱���������" << std::endl;
			}
			else if (playerSelect == 3) {
				player.showPStat();
			}
			else {
				continue;
			}
		}
		if (monster.HP <= 0) {
			continue;
		}

		std::cout << "��� " << monster.name << "�� ����!" << std::endl;
		while (1) {
			monsterSelect = 1;
			if (monsterSelect == 1) {
				std::cout << "��� " << monster.name << "�� ����!" << std::endl;
				player.HP -= dmg(monster, player);
				break;
			}
			else if (monsterSelect == 2) {
				std::cout << "��ų�� ���� �̱���������" << std::endl;
			}
			else {
				continue;
			}
		}
	}
	if (player.HP > monster.HP) {
		std::cout << monster.name << "���� ���� �¸��ߴ�!" << std::endl;
		Sleep(1000);
		Event(player, monster);
	}
}

int dmg(Actor attacker, Actor defender)
{
	int dmg = 0;
	dmg = attacker.ATK;
	std::cout << attacker.name << "��(��) " << defender.name << "���� " << dmg << "��ŭ�� ���ظ� ������!" << std::endl;
	return dmg;
}

void Event(Player& player, Monster& monster)
{
	std::cout << "�̺�Ʈ ����!" << std::endl;
	int playerSelect = 0;
	switch (monster.Event_index) {
	case 1:		//���ν�����
		std::cout << "1" << std::endl;
		std::cout << "1 or 2" << std::endl;
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			player.HP += (rand() % 5 + 1);
			player.addInventory(apple);
		}
		else if (playerSelect == 2) {
			player.HP += (rand() % 5 + 1);
			player.addInventory(orange);
		}
		break;
	case 2:		//������
		std::cout << "2" << std::endl;
		std::cout << "1 or 2" << std::endl;
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			player.HP += (rand() % 5 + 1);
			player.addInventory(grape);
		}
		else if (playerSelect == 2) {
			player.HP += (rand() % 5 + 1);
			player.addInventory(avocado);
		}
		break;
	case 3:		//�ֻ��
		std::cout << "3" << std::endl;
		std::cout << "1 or 2" << std::endl;
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			player.HP += (rand() % 5 + 1);
			player.addInventory(orange);
		}
		else if (playerSelect == 2) {
			player.HP += (rand() % 5 + 1);
			player.addInventory(watermelon);
		}
		break;
	case 4:		//����ü
		std::cout << "4" << std::endl;
		std::cout << "1 or 2" << std::endl;
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			player.HP += (rand() % 5 + 1);
			player.addInventory(orange);
		}
		else if (playerSelect == 2) {
			player.HP += (rand() % 5 + 1);
			player.addInventory(grapefruit);
		}
		break;
	case 5:		//���� ����
		break;
	default:
		break;
	}
	Sleep(1000);
}

void afterBattle(Player& player)
{
	std::cout << "���� ������ �ö󰡴� ����� ���δ�!" << std::endl;
	int playerSelect = 0;
	
	while (1) {
		std::cout << "1. �ö󰣴� 2. �ָӴϸ� Ȯ���Ѵ� 3.������� ����� 4. ������ Ȯ���Ѵ�" << std::endl;
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			std::cout << player.name << "��(��) ������ ���ٵ�� ���� ������ ���ߴ�." << std::endl;
			Sleep(1000);
			break;
		}
		else if (playerSelect == 2) {
			player.showInventory();
		}
		else if (playerSelect == 3) {
			std::cout << "blend system�� ���� �̱���������" << std::endl;
		}
		else if (playerSelect == 4) {
			player.showPStat();
		}
		else {
			continue;
		}
	}
}
