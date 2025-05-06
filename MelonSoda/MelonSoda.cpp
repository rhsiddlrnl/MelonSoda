#include <iostream>
#include "Actor.h"
#include "Monster.h"
#include "Fruit.h"
#include "Player.h"
#include "Battle.h"

int main() {
	srand(time(NULL));
	std::string player_Name;

	std::cout << "성함을 입력해주세요 : ";
	std::getline(std::cin, player_Name);

	Player player(player_Name);
	player.showPStat();

	Monster monster1("돼지", 20, 0, 5, 5);
	Monster monster2("소", 10, 0, 5, 5);
	Battle(player, monster1);
	afterBattle(player);
	Battle(player, monster2);
	afterBattle(player);
	return 0;
}
