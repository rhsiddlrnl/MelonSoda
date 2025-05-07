#include <iostream>
#include "Actor.h"
#include "Monster.h"
#include "Fruit.h"
#include "Player.h"
#include "Battle.h"

int main() {
	srand(time(NULL));
	std::map<int, Monster> monsterMap = {
		{1, slime},
		{2, king_slime},
		{3, waterrat},
		{5, chandelier}
	};

	std::string player_Name;

	std::cout << "성함을 입력해주세요 : ";
	std::getline(std::cin, player_Name);

	Player player(player_Name);
	player.showPStat();
	GAME(player, monsterMap);
	return 0;
}
