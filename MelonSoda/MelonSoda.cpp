#include <iostream>
#include "Actor.h"
#include "Monster.h"
#include "Fruit.h"
#include "Player.h"
#include "Battle.h"
#include "UIManager.h"

int main() {
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	//srand(time(NULL));
	std::system("mode con: cols=200 lines=50");
	std::string player_Name;
	Player player;


	G_UI->PrintTitle();
	std::getline(std::cin, player_Name);

	player.Setname(player_Name);
	

	delete G_UI;
	G_UI = new UIManager(&player, &zero);
	G_UI->clearALL();

	//인트로 너무 길어서 함수로 묶어놨습니다.
	G_UI->PrintIntro();

	G_UI->clearALL();

	//Monster monster1("돼지", 20, 0, 5, 5);
	//Monster monster2("소", 10, 0, 5, 5);
	//Battle(player, monster1);
	//afterBattle(player);
	//Battle(player, monster2);
	//afterBattle(player);

	/*G_UI = new UIManager(&player, &witch);
	G_UI->RefreshScreen();
	Battle(player, witch);*/


	GAME(player, monsterMap);
	return 0;
}
