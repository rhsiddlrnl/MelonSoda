#include "Battle.h"

void Battle(Player& player, Monster& monster)
{
	std::cout << monster.name << "이(가) 나타났다!" << std::endl;
	while ((player.HP > 0) && (monster.HP > 0)) {
		std::cout << player.name << "의 차례!" << std::endl;
		int playerSelect = 0;
		int monsterSelect = 0;		//몬스터 ai 구현용
		while (1) {
			std::cout << "무엇을 할까?" << std::endl;
			std::cout << "1. 공격 2. 스킬 3. 스탯확인" << std::endl;
			std::cin >> playerSelect;
			if (playerSelect == 1) {
				monster.HP -= dmg(player, monster);
				break;
			}
			else if (playerSelect == 2) {
				std::cout << "스킬은 아직 미구현이지비" << std::endl;
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

		std::cout << "상대 " << monster.name << "의 차례!" << std::endl;
		while (1) {
			monsterSelect = 1;
			if (monsterSelect == 1) {
				std::cout << "상대 " << monster.name << "의 공격!" << std::endl;
				player.HP -= dmg(monster, player);
				break;
			}
			else if (monsterSelect == 2) {
				std::cout << "스킬은 아직 미구현이지비" << std::endl;
			}
			else {
				continue;
			}
		}
	}
	if (player.HP > monster.HP) {
		std::cout << monster.name << "으로 부터 승리했다!" << std::endl;
		Sleep(1000);
		Event(player, monster);
	}
}

int dmg(Actor attacker, Actor defender)
{
	int dmg = 0;
	dmg = attacker.ATK;
	std::cout << attacker.name << "이(가) " << defender.name << "에게 " << dmg << "만큼의 피해를 입혔다!" << std::endl;
	return dmg;
}

void Event(Player& player, Monster& monster)
{
	std::cout << "이벤트 시작!" << std::endl;
	int playerSelect = 0;
	switch (monster.Event_index) {
	case 1:		//빵부스러기
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
	case 2:		//슬라임
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
	case 3:		//주사기
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
	case 4:		//실험체
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
	case 5:		//보스 진입
		break;
	default:
		break;
	}
	Sleep(1000);
}

void afterBattle(Player& player)
{
	std::cout << "다음 층으로 올라가는 계단이 보인다!" << std::endl;
	int playerSelect = 0;
	
	while (1) {
		std::cout << "1. 올라간다 2. 주머니를 확인한다 3.음료수를 만든다 4. 스탯을 확인한다" << std::endl;
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			std::cout << player.name << "은(는) 마음을 가다듬고 다음 층으로 향했다." << std::endl;
			Sleep(1000);
			break;
		}
		else if (playerSelect == 2) {
			player.showInventory();
		}
		else if (playerSelect == 3) {
			std::cout << "blend system은 아직 미구현이지비" << std::endl;
		}
		else if (playerSelect == 4) {
			player.showPStat();
		}
		else {
			continue;
		}
	}
}
