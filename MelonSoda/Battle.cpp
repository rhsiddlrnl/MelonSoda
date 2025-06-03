#include "Battle.h"
#include "Monster.h"
#include "Player.h"
#include "UIManager.h"

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <string>

//배틀 함수는 궁금하면 읽어보고 이해하셔요
void Battle(Player& player, Monster& monster)
{
	// 엔딩 분기
	bool didselect = FALSE;
	bool didevent = FALSE;
	
	if (auto bossPtr = dynamic_cast<Boss*>(&monster)) {
		if (!didevent) {
			G_UI->PrintLog("이벤트 BOSS <누군가에겐 '참'이될 이야기>");
			G_UI->PrintLog("마녀(???) : 그렇게 헤집고 다니는게 취미야?");
			G_UI->PrintLog("            너 바보야? 하... 그거 다 결계인데 좋다고 주워온거야?");
			G_UI->PrintLog("            더 이상 나도 못참아 각오하는게 좋을거야. 난 호락호락하지 않다고");
			Sleep(2000);
			G_UI->PrintLog("용사 : 갑작스럽지만 주인장이 화나 바로 준비를 해야할 것 같다.");
			G_UI->PrintLog(player.name, " (은)는 마음을 다잡고 칼을 들었다");
			G_UI->PrintLog("전투에 돌입하자....!");
			Sleep(2000);
			didevent = TRUE;
		}
	}

	G_UI->PrintLog(monster.name, " 이(가) 나타났다!");
	while ((player.HP > 0) && (monster.HP > 0)) {
		G_UI->PrintLog(player.name, "의 차례");
		int playerSelect = 0;
		int monsterSelect = 0;		//몬스터 ai 구현용
		while (1) {
			G_UI->PrintLog("무엇을 할까?");
			G_UI->PrintLog("1. 공격 2. 스킬");
			G_UI->PrintLog("");
			std::cin >> playerSelect;

			if (playerSelect == 1) {
				G_UI->showLog();
				int damage = dmg(player, monster);
				monster.HP -= damage;

				//마지막 공격력 저장
				player.lastDamage = damage;
				monster.hitDamage += damage;

				//참기 +1 및 능력치 증가
				player.addConcentration();
				break;
			}
			else if (playerSelect == 2) {
				if (player.useSkill(monster)) {
					continue;
				};
				break;
				//std::cout << "스킬은 아직 미구현이지비" << std::endl;
			}
			/*else if (playerSelect == 3) {
				player.showPStat();
			}*/
			else {
				continue;
			}
		}
		if (monster.HP <= 0) {
			continue;
		}
		G_UI->PrintLog(monster.name, "의 현재 체력은 ", monster.HP);

		//몬스터 턴
		G_UI->incrementLine(1);
		G_UI->moveCursorTo(0, G_UI->getLine());
		G_UI->PrintLog("상대 ", monster.name, "의 차례!");
		Sleep(1000);
		// 보스인지 판별
		while (1) {
			if (auto bossPtr = dynamic_cast<Boss*>(&monster)) {
				int roll = (std::rand() % 100) + 1;
				if (roll <= 30) {
					// 60% 확률 일반 공격
					G_UI->PrintLog( "상대 " , monster.name , "의 일반 공격!");
					int damage = dmg(monster, player);
					// 튕겨내기 효과
					if (player.isReflecting) {
						damage = static_cast<int>(damage * 0.7);
						G_UI->PrintLog( "- 튕겨내기 효과로 데미지가 감소되었습니다! (", damage,")");
						player.isReflecting = false;
					}
					player.HP -= damage;
					player.hitDamage += damage;
				}
				else {
					// 스킬 공격 (랜덤하게 세 가지 중 하나)
					
					int n = 3;
					int idx = rand() % n;
					if (idx == 0) {
						if (bossPtr->overturnFuture()) 
						{
							//G_UI->incrementLine(1);
							//G_UI->moveCursorTo(0, G_UI->getLine());
							//G_UI->PrintLog("다시보스턴");
							//G_UI->moveCursorTo(0, G_UI->getLine());
							continue;
						}
						//G_UI->PrintLog("상대 ", monster.name, "의 스킬 공격!");
						G_UI->PrintLog( "[스킬] 너만 모르는 이야기");
						G_UI->moveCursorTo(0, G_UI->getLine());

					}
					else if (idx == 1) {
						if (bossPtr->heavensDoor(player)) 
						{
							//G_UI->incrementLine(1);
							//G_UI->moveCursorTo(0, G_UI->getLine());
							//G_UI->PrintLog("다시보스턴");
							//G_UI->moveCursorTo(0, G_UI->getLine());
							continue;
						}
						//G_UI->PrintLog("상대 ", monster.name, "의 스킬 공격!");
						G_UI->PrintLog("[스킬] 너만 모르는 이야기");
						G_UI->moveCursorTo(0, G_UI->getLine());
					}
					else {
						if (bossPtr->otherworldlyBlade(player)) 
						{
							//G_UI->incrementLine(1);
							//G_UI->moveCursorTo(0, G_UI->getLine());
							//G_UI->PrintLog("다시보스턴");
							//G_UI->moveCursorTo(0, G_UI->getLine());
							continue;
							continue;
						}
						//G_UI->PrintLog("상대 ", monster.name, "의 스킬 공격!");
						G_UI->PrintLog("[스킬] 너만 모르는 이야기");
						G_UI->moveCursorTo(0, G_UI->getLine());
					}
				}

				monster.MP += 2;


				
				if (!didselect && monster.HP <= 60) {
					int endingselect = 0;
					G_UI->PrintLog("마녀(???) : 음? 생각보다 잘 싸우네.. 이미 '효과'는 뿌리내렸을텐데..");
					G_UI->PrintLog( "            너. 나랑 같이 이 도시의 진실을 파헤쳐보지 않겠어?");
					G_UI->PrintLog("용사 : 갑자기 무슨 소리냐?");
					G_UI->PrintLog("마녀(???) : 너가 알고 싶다던 진실을 알려줄게 내가 왜 멜론에 '독'을 풀었는지");
					G_UI->PrintLog("결정해야할 것 같다.. 뭐지 갑자기 이런 제안을 하는 이유가?");
					G_UI->PrintLog("1. 자세한 이야기를 들어본다. | 2. 슬슬 체력이 다해 쪼들리는거냐!!!!");
					G_UI->PrintLog("");
					std::cin >> endingselect;
					if (endingselect == 1) {
						monster.Event_index = 7;
						Event(player, monster);
					}
					didselect = TRUE;
				}
				// 보스 턴 후 자동 회복 & 미래 스택 획득
				bossPtr->regeneratePerTurn();

				//확인 용이하게 입력받아야 넘어가게 해둔 테스트용
				/*std::cin >> playerSelect;*/

				_getch();

				G_UI->RefreshStats();
				G_UI->showPstats(player.hitDamage);
				G_UI->showMstats(monster.hitDamage);
				G_UI->showLog();

				player.hitDamage = 0;
				monster.hitDamage = 0;

				break;
			}

			if (monster.Event_index == 7) {
				break;
			}
			else {
				// 일반 몬스터는 무조건 일반 공격
				G_UI->PrintLog("상대 ", monster.name , "의 공격!");
				int damage = dmg(monster, player);

				// 튕겨내기 효과
				if (player.isReflecting) {
					damage = static_cast<int>(damage * 0.7);
					G_UI->PrintLog("- 튕겨내기 효과로 데미지가 감소되었습니다! (", damage, ")");
					player.isReflecting = false;
				}
				player.HP -= damage;
				player.hitDamage += damage;

				//확인 용이하게 입력받아야 넘어가게 해둔 테스트용
				/*std::cin >> playerSelect;*/


				_getch();

				G_UI->RefreshStats();
				G_UI->showPstats(player.hitDamage);
				G_UI->showMstats(monster.hitDamage);
				G_UI->showLog();

				player.hitDamage = 0;
				monster.hitDamage = 0;

				break;
			}
		}
		
	}
	if (player.HP > 0) {
		if (monster.Event_index < 7) {
			G_UI->PrintLog( monster.name, "으로 부터 승리했다!" );
			G_UI->PrintLog("");
		}
		
		Sleep(1000);

		G_UI->RefreshStats();
		G_UI->showPstats(player.hitDamage);
		G_UI->showMstats(monster.hitDamage);
		G_UI->showLog();

		Event(player, monster);
	}
	else {
		G_UI->PrintLog("패배하고 말았다...");
		G_UI->PrintLog("");
		//패배 엔딩
		monster.Event_index = 8;
		Event(player, monster);
	}
}

int dmg(Actor attacker, Actor defender)
{
	int att = attacker.ATK;
	int def = defender.DEF;

	int damage = (att * 100) / (def + 100);
	G_UI->PrintLog( attacker.name , "이(가) " , defender.name , "에게 " , damage , "만큼의 피해를 입혔다!");
	return damage;
}


void Event(Player& player, Monster& monster)
{
	G_UI->showLog();
	G_UI->PrintLog("");
	int playerSelect = 0;
	switch (monster.Event_index) {
	case 1:		//빵부스러기
		G_UI->PrintLog("Event 1 <웬 빵부스러기?>");
		G_UI->PrintLog("뭐야 ? 왜 여기에 느닷없이 빵 부스러기가 큼직큼직하게 떨어져 있냐 ? ? 가볼까 ?");
		G_UI->PrintLog("");
		G_UI->PrintLog("1.그래 | 2. 놉 미쳤어? 이런 곳에 있는 걸?");
		G_UI->PrintLog("");
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			G_UI->PrintLog("용사 : 이런 곳에 있으면 빵이 불쌍...? 뭐야 이건... 오렌지?(오랜지 획득)");
			player.addInventory(orange);
			G_UI->PrintLog( "잠깐 쉬니까 몸이 좀 회복 되는구만.. 가볼까?");
			int heal = rand() % 5 + 1;
			player.HP += heal;
			G_UI->PrintLog( "플레이어의 HP ", heal, " 만큼 회복!");

		}
		else if (playerSelect == 2) {
			G_UI->PrintLog( "용사 : 아니아니 상식적으로 이렇게 깨끗한 곳에 부스러기가 떨어져 있을리가 없잖아....?");
			G_UI->PrintLog("       무시하고 가ㄹ..? 뭐냐 넌..?");
			G_UI->PrintLog("유령 : (아무 말 없이 용사의 손을 꼭 잡고 무언가를 쥐여준다)");
			G_UI->PrintLog("용사 : 사과...? (사과 획득)");

			player.addInventory(apple);
			G_UI->PrintLog("잠깐 쉬니까 몸이 좀 회복 되는구만.. 가볼까?");
			int heal = rand() % 5 + 1;
			player.HP += heal;
			G_UI->PrintLog("플레이어의 HP " , heal , " 만큼 회복!");
		}
		break;
	case 2:	// 슬라임
		G_UI->PrintLog("Event 2 <생각보다 귀여운 슬라임>");
		G_UI->PrintLog("여긴 왜 슬라임만 있는거야? 슬라임 농사라도 짓는거냐고");
		G_UI->PrintLog("음? 저 슬라임은 좀 특이한데 가볼까??");
		G_UI->PrintLog("");
		G_UI->PrintLog("1. 그래 가보자 | 2. 아니아니 먹힐 일 있어??");
		G_UI->PrintLog("");
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			G_UI->PrintLog("용사 : 으왓!(손을 황급히 빼며) 뭐 이리 뜨겁냐?");
			G_UI->PrintLog("슬라임 : (미안한지 무언가를 뱉어낸다)");
			G_UI->PrintLog("용사 : 응? 선물이야? 포도..? 뭐지 여긴 과일 재배지인가?");
			G_UI->PrintLog("        얘는 왜 차가운거야?(포도 획득)");
			player.addInventory(grape);

			G_UI->PrintLog("잠깐 쉬니까 몸이 좀 회복 되는구만.. 가볼까?");
			int heal = rand() % 5 + 1;
			player.HP += heal;
			G_UI->PrintLog("플레이어의 HP ", heal, " 만큼 회복!");
		}
		else if (playerSelect == 2) {
			G_UI->PrintLog("용사 : 안 그래도 몬스터인데 뭔가 먹고 있다고.. 무섭게 뜨거워! 나는 쟤 먹이가 되기 싫어!");
			G_UI->PrintLog("용사는 황급히 자리를 뜬다.");
			G_UI->PrintLog("다음 방으로 가던 중 무언가가 하늘에서 떨어진다.");
			G_UI->PrintLog("용사 : 아얏! 누구야? 아보카..도..? (아보카도 획득!)");
			player.addInventory(avocado);

			G_UI->PrintLog("잠깐 쉬니까 몸이 좀 회복 되는구만.. 가볼까?");
			int heal = rand() % 5 + 1;
			player.HP += heal;
			G_UI->PrintLog("플레이어의 HP ", heal, " 만큼 회복!");
		}
		break;

	case 3: // 주사기
		G_UI->PrintLog("Event 3 <의문의 주사기>");
		G_UI->PrintLog("이건 또 뭐야? 떡하니 주사기가 저 써주세요하는데? 어쩔까?");
		G_UI->PrintLog("");
		G_UI->PrintLog("1. 짱짱 세지는 것 같은데 지금 당장하자. 2. 이런 곳에 있는 주사기라고? 당연히 안되지");
		G_UI->PrintLog("");
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			G_UI->PrintLog("용사 : (주사한 곳을 누르며)오! 이거 좋은데? 멜론 소다를 먹은 느낌이었어!");
			G_UI->PrintLog("       (주사기가 들어있던 상자에 손을 넣으며) 또 뭔가 있는데? 하... 이번엔 오렌지냐....");
			player.addInventory(orange);

			G_UI->PrintLog("잠깐 쉬니까 몸이 좀 회복 되는구만.. 가볼까?");
			int heal = rand() % 5 + 1;
			player.HP += heal;
			G_UI->PrintLog("플레이어의 HP ", heal, " 만큼 회복!");
		}
		else if (playerSelect == 2) {
			G_UI->PrintLog("저 멀리에서 무언가가 총총하고 뛰어온다.");
			G_UI->PrintLog("용사 : 누ㄱ.. 어 슬라임 또 너냐? 나 맛없어");
			G_UI->PrintLog("       응? 이걸 또 나한테 준다고? 너는 몸은 용광로인데 내뱉는 것들은 왜 차갑냐?");
			G_UI->PrintLog("       (뱉은 곳에 다가가며)이번엔 뭘 주나? 음 수박이네... (웃으며)언럭키 멜론~!");
			player.addInventory(watermelon);

			G_UI->PrintLog("잠깐 쉬니까 몸이 좀 회복 되는구만.. 가볼까?");
			int heal = rand() % 5 + 1;
			player.HP += heal;
			G_UI->PrintLog("플레이어의 HP ", heal, " 만큼 회복!");
		}
		break;

	case 4: // 실험체
		G_UI->PrintLog("Event 4 <너도 실험체?>");
		G_UI->PrintLog("용사 : 피로하구만 예전같지 않게 몸이 많이 둔해진 것 같아..");
		G_UI->PrintLog("뒤에서 무슨 소리가 들려 돌아본다");
		G_UI->PrintLog("XX : 삣삐삣삐!");
		G_UI->PrintLog("용사 : 많이 피곤한가봐.... 별 이상한 소리가 들리네");
		G_UI->PrintLog("음... 집에서 마법서 가져오긴 했는데 해석해볼까?");
		G_UI->moveCursorTo(0, G_UI->getLine());
		G_UI->PrintLog("1. 무슨 말 할지 기대가 된다 2. 별 중요한 얘기도 아니겠지 칼을 뽑는다");
		G_UI->PrintLog("");
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			G_UI->PrintLog("XX : 삣삐삣삐!");
			G_UI->PrintLog("용사 : 뭐야? 진짜 삣삐삣삐라고 말한거였잖아!");
			G_UI->PrintLog("XX는 다가오더니 앞에 무언가를 내려놓았다.");
			G_UI->PrintLog("용사 : 하하하... 여기는 미쳤어... 또 과일이야...");
			G_UI->PrintLog("       그래그래... 고맙다.... (오렌지 획득)");
			player.addInventory(orange);

			G_UI->PrintLog("잠깐 쉬니까 몸이 좀 회복 되는구만.. 가볼까?");
			int heal = rand() % 5 + 1;
			player.HP += heal;
			G_UI->PrintLog("플레이어의 HP ", heal, " 만큼 회복!");
		}
		else if (playerSelect == 2) {
			G_UI->PrintLog("용사 : 뭐라는지 하나도 모르겠어! 죽x어!");
			G_UI->PrintLog("반짝반짝거리는 무언가가 떨어졌다.");
			G_UI->PrintLog("용사 : 그래그래 이것도 과일이네 완전히 깨달았어! 여기는 미친 곳이야!(자몽획득)");
			player.addInventory(grapefruit);

			G_UI->PrintLog("잠깐 쉬니까 몸이 좀 회복 되는구만.. 가볼까?");
			int heal = rand() % 5 + 1;
			player.HP += heal;
			G_UI->PrintLog("플레이어의 HP ", heal, " 만큼 회복!");
		}
		break;

	case 5: // 보스
		G_UI->PrintLog("이벤트 BOSS <누군가에겐 '참'이될 이야기>");
		G_UI->PrintLog("마녀(???) : 그렇게 헤집고 다니는게 취미야?");
		G_UI->PrintLog("            너 바보야? 하... 그거 다 결계인데 좋다고 주워온거야?");
		G_UI->PrintLog("            더 이상 나도 못참아 각오하는게 좋을거야. 난 호락호락하지 않다고");
		Sleep(2000);
		G_UI->PrintLog("용사 : 갑작스럽지만 주인장이 화나 바로 준비를 해야할 것 같다.");
		G_UI->PrintLog(player.name, " (은)는 마음을 다잡고 칼을 들었다");
		G_UI->PrintLog("전투에 돌입하자....!");
		Sleep(2000);
		break;

	case 6: // 엔딩
		G_UI->clearALL();
		G_UI->PrintLog("<NORMAL엔딩> 다시라는 말은");
		Sleep(2000);
		G_UI->PrintLog("마녀를 쓰러뜨린 후 나는 곧장 마을로 돌아가 마녀를 처단했다는 소식을 전했다.");
		G_UI->PrintLog("도시는 며칠간 술렁였지만 머지않아 곧 잠잠해지겠지....");
		Sleep(1000);
		G_UI->PrintLog("용사 : 예전처럼 멜론소다도 다시팔기 시작했고, 모든게 좋아진거야...");
		G_UI->PrintLog("       그런데 왜이리 둔하고 찝찝한 느낌만 드는걸까..?");
		Sleep(2000);
		exit(1);
		break;
	case 7:
		G_UI->PrintTrueEnd();

		exit(1);
	case 8:
		G_UI->PrintLog( "아직... 여기서 죽을 순 없어... 멜론소다의 진실을 파헤쳐야..해.!" );
		G_UI->PrintLog( "다시 도전해보자");
		exit(1);
	default:
		break;
	}
	Sleep(1000);
}

void afterBattle(Player& player)
{
	G_UI->PrintLog( "다음 층으로 올라가는 계단이 보인다!");
	int playerSelect = 0;
	
	while (1) {
		G_UI->PrintLog("");
		G_UI->PrintLog( "1. 올라간다 2. 주머니를 확인한다 3.음료수를 만든다.");
		G_UI->PrintLog("");
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			G_UI->PrintLog( player.name , "은(는) 마음을 가다듬고 다음 층으로 향했다.");
			Sleep(1000);
			break;
		}
		else if (playerSelect == 2) {
			player.showInventory();
			Sleep(1000);
		}
		else if (playerSelect == 3) {
			G_UI->showLog();
			G_UI->PrintLog("");
			int fruitSelect1 = 0;
			int fruitSelect2 = 0;
			G_UI->PrintLog( "무슨 과일로 만들까?");
			G_UI->PrintLog("");
			player.showInventory();
			G_UI->PrintLog("");
			//std::cout << player.fruit_inventory.size() << std::endl;
			std::cin >> fruitSelect1;
			if (fruitSelect1 > player.fruit_inventory.size()) {
				G_UI->PrintLog( "가지고 있지 않는 것 같다..." );
				Sleep(1000);
				G_UI->showLog();
				continue;
			}
			std::cin >> fruitSelect2;
			if (fruitSelect1 == fruitSelect2) {
				G_UI->PrintLog( "이미 선택한 과일이다..." );
				Sleep(1000);
				G_UI->showLog();
				continue;
			}
			if (fruitSelect2 > player.fruit_inventory.size()) {
				G_UI->PrintLog( "가지고 있지 않는 것 같다..." );
				Sleep(1000);
				G_UI->showLog();
				continue;
			}
			G_UI->PrintLog( player.fruit_inventory[fruitSelect1 - 1].name , "와(과)" , player.fruit_inventory[fruitSelect2 - 1].name , "을(를) 사용해서 음료를 만들까?");
			G_UI->PrintLog("1. 당장 만들자! 2. 다시 생각해보자");
			G_UI->PrintLog("");
			std::cin >> playerSelect;
			if (playerSelect == 1) {
				player.blendFruit(player.fruit_inventory[fruitSelect1 - 1], player.fruit_inventory[fruitSelect2 - 1]);
				Sleep(3000);
			}
			else {
				Sleep(1000);
				G_UI->showLog();
				continue;
			}
		}
		/*else if (playerSelect == 4) {
			player.showPStat();
		}*/
		else {
			continue;
		}
	}
}

void GAME(Player& player, const std::map<int, Monster*>& monsterMap)
{
	for (auto it = monsterMap.begin(); it != monsterMap.end(); ++it) 
	{
		Monster* mptr = it->second;

		delete G_UI;
		G_UI = new UIManager(&player, &*mptr);

		if (G_UI == NULL)
		{
			std::cout << "에러 발생 G_UI가 널포인터를 가르킴";
			std::abort();
		}

		G_UI->clearALL();
		G_UI->RefreshScreen();

		Battle(player, *mptr);

		Sleep(3000);
		G_UI->clearALL();
		G_UI->RefreshScreen();

		afterBattle(player);
	}
}