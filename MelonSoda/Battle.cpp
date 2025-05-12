#include "Battle.h"

//��Ʋ �Լ��� �ñ��ϸ� �о�� �����ϼſ�
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
				int damage = dmg(player, monster);
				monster.HP -= damage;

				//������ ���ݷ� ����
				player.lastDamage = damage;
				//���� +1 �� �ɷ�ġ ����
				player.addConcentration();
				break;
			}
			else if (playerSelect == 2) {
				player.useSkill(monster);
				break;
				//std::cout << "��ų�� ���� �̱���������" << std::endl;
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
		std::cout << monster.name << "�� ���� ü���� " << monster.HP << std::endl;

		//���� ��
		std::cout << std::endl;
		std::cout << "��� " << monster.name << "�� ����!" << std::endl;
		Sleep(1000);
		while (1) {
			monsterSelect = 1;
			if (monsterSelect == 1) {
				std::cout << "��� " << monster.name << "�� ����!" << std::endl;
				int damage = dmg(monster, player);  //���� ������ ���
				if (player.isReflecting) {
					damage = static_cast<int>(damage * 0.7);  //30% ����
					std::cout << "- ƨ�ܳ��� ȿ���� �������� ���ҵǾ����ϴ�! (" << damage << ")\n";
					player.isReflecting = false;  //ȿ�� 1�ϸ�
				}

				player.HP -= damage;
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
	else {
		std::cout << "�й��ϰ� ���Ҵ�..." << std::endl;
		exit(1);
	}
}

int dmg(Actor attacker, Actor defender)
{
	int att = attacker.ATK;
	int def = defender.DEF;

	int damage = (att * 100) / (def + 100);
	std::cout << attacker.name << "��(��) " << defender.name << "���� " << damage << "��ŭ�� ���ظ� ������!" << std::endl;
	return damage;
}


void Event(Player& player, Monster& monster)
{
	std::cout << std::endl;
	int playerSelect = 0;
	switch (monster.Event_index) {
	case 1:		//���ν�����
		std::cout << "Event 1 <�� ���ν�����?>\n����? �� ���⿡ ������� �� �ν����Ⱑ ŭ��ŭ���ϰ� ������ �ֳ�?? ������?\n" << std::endl;
		std::cout << "1.�׷� | 2. �� ���ƾ�? �̷� ���� �ִ� ��?\n" << std::endl;
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			std::cout << "��� : �̷� ���� ������ ���� �ҽ�...? ���� �̰�... ������?(������ ȹ��)\n" << std::endl;
			player.addInventory(apple);
			std::cout << "��� ���ϱ� ���� �� ȸ�� �Ǵ±���.. ������?" << std::endl;
			int heal = rand() % 5 + 1;
			player.HP += heal;
			std::cout << "�÷��̾��� HP " << heal << " ��ŭ ȸ��!" << std::endl;

		}
		else if (playerSelect == 2) {
			std::cout << "��� : �ƴϾƴ� ��������� �̷��� ������ ���� �ν����Ⱑ ������ �������� ���ݾ�....?" << std::endl;
			std::cout << "       �����ϰ� ����..? ���� ��..?" << std::endl;
			std::cout << "���� : (�ƹ� �� ���� ����� ���� �� ��� ���𰡸� �㿩�ش�)" << std::endl;
			std::cout << "��� : ���...? (��� ȹ��)" << std::endl;

			player.addInventory(orange);
			std::cout << "��� ���ϱ� ���� �� ȸ�� �Ǵ±���.. ������?" << std::endl;
			int heal = rand() % 5 + 1;
			player.HP += heal;
			std::cout << "�÷��̾��� HP " << heal << " ��ŭ ȸ��!" << std::endl;
		}
		break;
	case 2:		//������
		std::cout << "Event 2 <�������� �Ϳ��� ������>\n���� �� �����Ӹ� �ִ°ž�? ������ ���� ���°ųİ�\n��? �� �������� �� Ư���ѵ� ������??\n" << std::endl;
		std::cout << "1. �׷� ������ | 2. �ƴϾƴ� ���� �� �־�??" << std::endl;
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			std::cout << "��� : ����!(���� Ȳ���� ����) �� �̸� �̳߰�?" << std::endl;
			std::cout << "������ : (�̾����� ���𰡸� ����)" << std::endl;
			std::cout << "��� : ��? �����̾�? ����..? ���� ���� ���� ������ΰ�?" << std::endl;
			std::cout << "        ��� �� ������ž�?(���� ȹ��)" << std::endl;

			player.addInventory(grape);
			std::cout << "��� ���ϱ� ���� �� ȸ�� �Ǵ±���.. ������?" << std::endl;
			int heal = rand() % 5 + 1;
			player.HP += heal;
			std::cout << "�÷��̾��� HP " << heal << " ��ŭ ȸ��!" << std::endl;
		}
		else if (playerSelect == 2) {
			std::cout << "��� : �ƴ� �ȱ׷��� �����ε� �� ���� �԰� �ִٰ�.. �׸��� ������ �߰ſ�! ���� �� ���̰� �Ǳ� �Ⱦ�!" << std::endl;
			std::cout << "���� Ȳ���� �ڸ��� ���." << std::endl;
			std::cout << "���� ������ ���� �� ���𰡰� �ϴÿ��� ��������." << std::endl;
			std::cout << "��� : �ƾ�! ������? �ƺ�ī..��..?(�ƺ�ī�� ȹ��!)" << std::endl;

			player.addInventory(avocado);
			std::cout << "��� ���ϱ� ���� �� ȸ�� �Ǵ±���.. ������?" << std::endl;
			int heal = rand() % 5 + 1;
			player.HP += heal;
			std::cout << "�÷��̾��� HP " << heal << " ��ŭ ȸ��!" << std::endl;
		}
		break;
	case 3:		//�ֻ��
		std::cout << "Event 3 <�ǹ��� �ֻ��>\n�̰� �� ����? ���ϴ� �ֻ�Ⱑ �� ���ּ����ϴµ�? ��¿��?\n" << std::endl;
		std::cout << "1. ¯¯ ������ �� ������ ���� ��������. 2. �̷� ���� �ִ� �ֻ����? �翬�� �ȵ���\n" << std::endl;
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			std::cout << "��� : (�ֻ��� ���� ������)��! �̰� ������? ��� �Ҵٸ� ���� �����̾���!" << std::endl;
			std::cout << "       (�ֻ�Ⱑ ����ִ� ���ڿ� ���� ������) �� ���� �ִµ�? ��... �̹��� ��������...." << std::endl;

			player.addInventory(orange);
			std::cout << "��� ���ϱ� ���� �� ȸ�� �Ǵ±���.. ������?" << std::endl;
			int heal = rand() % 5 + 1;
			player.HP += heal;
			std::cout << "�÷��̾��� HP " << heal << " ��ŭ ȸ��!" << std::endl;
		}
		else if (playerSelect == 2) {
			std::cout << "�� �ָ����� ���𰡰� �����ϰ� �پ�´�." << std::endl;
			std::cout << "��� : ����.. �� ������ �� �ʳ�? �� ������" << std::endl;
			std::cout << "       ��? �̰� �� ������ �شٰ�? �ʴ� ���� �뱤���ε� ����� �͵��� �� ������?" << std::endl;
			std::cout << "       (���� ���� �ٰ�����)�̹��� �� �ֳ�? �� �����̳�... (������)��Ű ���~!" << std::endl;

			player.addInventory(watermelon);
			std::cout << "��� ���ϱ� ���� �� ȸ�� �Ǵ±���.. ������?" << std::endl;
			int heal = rand() % 5 + 1;
			player.HP += heal;
			std::cout << "�÷��̾��� HP " << heal << " ��ŭ ȸ��!" << std::endl;
		}
		break;
	case 4:		//����ü
		std::cout << "Event 4 <�ʵ� ����ü?>\n��� : �Ƿ��ϱ��� �������� �ʰ� ���� ���� ������ �� ����..\n�ڿ��� ���� �Ҹ��� ��� ���ƺ���\nXX : ��߻��!\n��� : ���� �ǰ��Ѱ���.... �� �̻��� �Ҹ��� �鸮��\n��... ������ ������ �������� �ߴµ� �ؼ��غ���?\n" << std::endl;
		std::cout << "1. ���� �� ���� ��밡 �ȴ� 2. �� �߿��� ��⵵ �ƴϰ��� Į�� �̴´�\n" << std::endl;
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			std::cout << "XX : ��߻��!" << std::endl;
			std::cout << "��� : ����? ��¥ ��߻�߶�� ���Ѱſ��ݾ�!" << std::endl;
			std::cout << "XX�� �ٰ������� �տ� ���𰡸� �������Ҵ�." << std::endl;
			std::cout << "��� : ������... ����� ���ƾ�... �� �����̾�..." << std::endl;
			std::cout << "       �׷��׷�... ����.... (������ ȹ��)" << std::endl;

			player.addInventory(orange);
			std::cout << "��� ���ϱ� ���� �� ȸ�� �Ǵ±���.. ������?" << std::endl;
			int heal = rand() % 5 + 1;
			player.HP += heal;
			std::cout << "�÷��̾��� HP " << heal << " ��ŭ ȸ��!" << std::endl;
		}
		else if (playerSelect == 2) {
			std::cout << "��� : ������� �ϳ��� �𸣰ھ�! ��x��!" << std::endl;
			std::cout << "��¦��¦�Ÿ��� ���𰡰� ��������." << std::endl;
			std::cout << "��� : �׷��׷� �̰͵� �����̳� ������ ���޾Ҿ�! ����� ��ģ ���̾�!(�ڸ�ȹ��)" << std::endl;

			player.addInventory(grapefruit);
			std::cout << "��� ���ϱ� ���� �� ȸ�� �Ǵ±���.. ������?" << std::endl;
			int heal = rand() % 5 + 1;
			player.HP += heal;
			std::cout << "�÷��̾��� HP " << heal << " ��ŭ ȸ��!" << std::endl;
		}
		break;
	case 5:		//���� ����
		std::cout << "Event BOSS<���������� '��'�� �� �̾߱�>\n����(???) : �� ��¥ ��� �׷��� ������ �ٴҲ���?\n           ��... ���� ����\n" << std::endl;
		std::cout << "�غ� �ؾ��� �� ����. Į�� ������ ������." << std::endl;
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
			std::cout << std::endl;
			int fruitSelect1 = 0;
			int fruitSelect2 = 0;
			std::cout << "���� ���Ϸ� �����?" << std::endl;
			player.showInventory();
			//std::cout << player.fruit_inventory.size() << std::endl;
			std::cin >> fruitSelect1;
			if (fruitSelect1 > player.fruit_inventory.size()) {
				std::cout << "������ ���� �ʴ� �� ����..." << std::endl;
				continue;
			}
			std::cin >> fruitSelect2;
			if (fruitSelect1 == fruitSelect2) {
				std::cout << "�̹� ������ �����̴�..." << std::endl;
				continue;
			}
			if (fruitSelect2 > player.fruit_inventory.size()) {
				std::cout << "������ ���� �ʴ� �� ����..." << std::endl;
				continue;
			}
			std::cout << player.fruit_inventory[fruitSelect1 - 1].name << "��(��)" << player.fruit_inventory[fruitSelect2 - 1].name << "��(��) ����ؼ� ���Ḧ �����?" << std::endl;
			std::cout << "1. ���� ������! 2. �ٽ� �����غ���" << std::endl;
			std::cin >> playerSelect;
			if (playerSelect == 1) {
				player.blendFruit(player.fruit_inventory[fruitSelect1 - 1], player.fruit_inventory[fruitSelect2 - 1]);
			}
			else {
				continue;
			}
		}
		else if (playerSelect == 4) {
			player.showPStat();
		}
		else {
			continue;
		}
	}
}

void GAME(Player& player, const std::map<int, Monster>& monsterMap)
{
	for (const auto& pair : monsterMap) {
		const Monster& monster = pair.second;
		Battle(player, const_cast<Monster&>(monster)); 
		afterBattle(player);
	}

}
