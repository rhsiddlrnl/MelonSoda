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
		std::cout << "Event 1 <웬 빵부스러기?>\n뭐야? 왜 여기에 느닷없이 빵 부스러기가 큼직큼직하게 떨어져 있냐?? 가볼까?\n" << std::endl;
		std::cout << "1.그래 | 2. 놉 미쳤어? 이런 곳에 있는 걸?\n" << std::endl;
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			std::cout << "용사 : 이런 곳에 있으면 빵이 불쌍...? 뭐야 이건... 오렌지?(오랜지 획득)\n" << std::endl;
			player.addInventory(apple);
			std::cout << "잠깐 쉬니까 몸이 좀 회복 되는구만.. 가볼까?" << std::endl;
			int heal = rand() % 5 + 1;
			player.HP += heal;
			std::cout << "플레이어의 HP : " << heal << " 만큼 회복!" << std::endl;
			
		}
		else if (playerSelect == 2) {
			std::cout << "용사 : 아니아니 상식적으로 이렇게 깨끗한 곳에 부스러기가 떨어져 있을리가 없잖아....?" << std::endl;
			std::cout << "       무시하고 가ㄹ..? 뭐냐 넌..?" << std::endl;
			std::cout << "유령 : (아무 말 없이 용사의 손을 꼭 잡고 무언가를 쥐여준다)" << std::endl;
			std::cout << "용사 : 사과...? (사과 획득)" << std::endl;
			
			player.addInventory(orange);
			std::cout << "잠깐 쉬니까 몸이 좀 회복 되는구만.. 가볼까?" << std::endl;
			int heal = rand() % 5 + 1;
			player.HP += heal;
			std::cout << "플레이어의 HP : " << heal << " 만큼 회복!" << std::endl;
		}
		break;
	case 2:		//슬라임
		std::cout << "Event 2 <생각보다 귀여운 슬라임>\n여긴 왜 슬라임만 있는거야? 슬라임 농사라도 짓는거냐고\n음? 저 슬라임은 좀 특이한데 가볼까??\n" << std::endl;
		std::cout << "1. 그래 가보자 | 2. 아니아니 먹힐 일 있어??" << std::endl;
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			std::cout << "용사 : 으왓!(손을 황급히 빼며) 뭐 이리 뜨겁냐?" << std::endl;
			std::cout << "슬라임 : (미안한지 무언가를 뱉어낸다)" << std::endl;
			std::cout << "용사 : 응? 선물이야? 포도..? 뭐지 여긴 과일 재배지인가?" << std::endl;
			std::cout << "        얘는 왜 차가운거야?(포도 획득)" << std::endl;

			player.addInventory(grape);
			std::cout << "잠깐 쉬니까 몸이 좀 회복 되는구만.. 가볼까?" << std::endl;
			int heal = rand() % 5 + 1;
			player.HP += heal;
			std::cout << "플레이어의 HP : " << heal << " 만큼 회복!" << std::endl;
		}
		else if (playerSelect == 2) {
			std::cout << "용사 : 아니 안그래도 몬스터인데 쟤 뭔가 먹고 있다고.. 그리고 무섭게 뜨거워! 나는 쟤 먹이가 되기 싫어!" << std::endl;
			std::cout << "용사는 황급히 자리를 뜬다." << std::endl;
			std::cout << "다음 방으로 가던 중 무언가가 하늘에서 떨어진다." << std::endl;
			std::cout << "용사 : 아얏! 누구야? 아보카..도..?(아보카도 획득!)" << std::endl;

			player.addInventory(avocado);
			std::cout << "잠깐 쉬니까 몸이 좀 회복 되는구만.. 가볼까?" << std::endl;
			int heal = rand() % 5 + 1;
			player.HP += heal;
			std::cout << "플레이어의 HP : " << heal << " 만큼 회복!" << std::endl;
		}
		break;
	case 3:		//주사기
		std::cout << "Event 3 <의문의 주사기>\n이건 또 뭐야? 떡하니 주사기가 저 써주세요하는데? 어쩔까?\n" << std::endl;
		std::cout << "1. 짱짱 세지는 것 같은데 지금 당장하자. 2. 이런 곳에 있는 주사기라고? 당연히 안되지\n" << std::endl;
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			std::cout << "용사 : (주사한 곳을 누르며)오! 이거 좋은데? 멜론 소다를 먹은 느낌이었어!" << std::endl;
			std::cout << "       (주사기가 들어있던 상자에 손을 넣으며) 또 뭔가 있는데? 하... 이번엔 오렌지냐...." << std::endl;

			player.addInventory(orange);
			std::cout << "잠깐 쉬니까 몸이 좀 회복 되는구만.. 가볼까?" << std::endl;
			int heal = rand() % 5 + 1;
			player.HP += heal;
			std::cout << "플레이어의 HP : " << heal << " 만큼 회복!" << std::endl;
		}
		else if (playerSelect == 2) {
			std::cout << "저 멀리에서 무언가가 총총하고 뛰어온다." << std::endl;
			std::cout << "용사 : 누ㄱ.. 어 슬라임 또 너냐? 나 맛없어" << std::endl;
			std::cout << "       응? 이걸 또 나한테 준다고? 너는 몸은 용광로인데 내뱉는 것들은 왜 차갑냐?" << std::endl;
			std::cout << "       (뱉은 곳에 다가가며)이번엔 뭘 주나? 음 수박이네... (웃으며)언럭키 멜론~!" << std::endl;

			player.addInventory(watermelon);
			std::cout << "잠깐 쉬니까 몸이 좀 회복 되는구만.. 가볼까?" << std::endl;
			int heal = rand() % 5 + 1;
			player.HP += heal;
			std::cout << "플레이어의 HP : " << heal << " 만큼 회복!" << std::endl;
		}
		break;
	case 4:		//실험체
		std::cout << "Event 4 <너도 실험체?>\n용사 : 피로하구만 예전같지 않게 몸이 많이 둔해진 것 같아..\n뒤에서 무슨 소리가 들려 돌아본다\nXX : 삣삐삣삐!\n용사 : 많이 피곤한가봐.... 별 이상한 소리가 들리네\n음... 집에서 마법서 가져오긴 했는데 해석해볼까?\n" << std::endl;
		std::cout << "1. 무슨 말 할지 기대가 된다 2. 별 중요한 얘기도 아니겠지 칼을 뽑는다\n" << std::endl;
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			std::cout << "XX : 삣삐삣삐!" << std::endl;
			std::cout << "용사 : 뭐야? 진짜 삣삐삣삐라고 말한거였잖아!" << std::endl;
			std::cout << "XX는 다가오더니 앞에 무언가를 내려놓았다." << std::endl;
			std::cout << "용사 : 하하하... 여기는 미쳤어... 또 과일이야..." << std::endl;
			std::cout << "       그래그래... 고맙다.... (오렌지 획득)" << std::endl;

			player.addInventory(orange);
			std::cout << "잠깐 쉬니까 몸이 좀 회복 되는구만.. 가볼까?" << std::endl;
			int heal = rand() % 5 + 1;
			player.HP += heal;
			std::cout << "플레이어의 HP : " << heal << " 만큼 회복!" << std::endl;
		}
		else if (playerSelect == 2) {
			std::cout << "용사 : 뭐라는지 하나도 모르겠어! 죽x어!" << std::endl;
			std::cout << "반짝반짝거리는 무언가가 떨어졌다." << std::endl;
			std::cout << "용사 : 그래그래 이것도 과일이네 완전히 깨달았어! 여기는 미친 곳이야!(자몽획득)" << std::endl;

			player.addInventory(grapefruit);
			std::cout << "잠깐 쉬니까 몸이 좀 회복 되는구만.. 가볼까?" << std::endl;
			int heal = rand() % 5 + 1;
			player.HP += heal;
			std::cout << "플레이어의 HP : " << heal << " 만큼 회복!" << std::endl;
		}
		break;
	case 5:		//보스 진입
		std::cout << "Event BOSS<누군가에겐 '참'이 될 이야기>\n마녀(???) : 너 진짜 계속 그렇게 헤집고 다닐꺼야?\n           하... 몰라 덤벼\n" << std::endl;
		std::cout << "준비를 해야할 것 같다. 칼을 서서히 꺼낸다." << std::endl;
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
