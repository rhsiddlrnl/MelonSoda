#include "Monster.h"
#include "Player.h"
#include "UIManager.h"

#include <iostream>

Monster::Monster(std::string monster_name, int monster_HP, int monster_MP, int monster_ATK, int monster_DEF, int event_index) {
	name = monster_name;
	HP = monster_HP;
	MP = monster_MP;
	ATK = monster_ATK;
	DEF = monster_DEF;
	Event_index = event_index;

    //전턴에 받은 데미지 임시저장
    hitDamage = 0;

}

void Monster::showMStat() {
    G_UI->PrintLog( "Name : ", name);
    G_UI->PrintLog("HP : ", HP);
}

//얘는 실행 안됨 오버라이드 목적 실행되면 강제종료
int Monster::Get_Stack()
{
    G_UI->clearALL();
    G_UI->PrintLog("몬스터의 가상함수 호출됨 이거 뜨면 에러");
    std::abort();
    return 0;
}

// Boss::regeneratePerTurn 구현
int Boss::regeneratePerTurn() {
    // HP 회복
    HP += 3;
    // 미래 스택 증가
	future += 1;
    G_UI->PrintLog( name , "은(는) HP 3 회복, 미래 스택 +1! " , "(HP: " , HP , ", 미래: " , future , ")");
    return 0;
}

int Boss::overturnFuture() {
    if (future < 5) {
        //G_UI->PrintLog( name, " : 미래 스택이 부족합니다. (필요:5, 현재:" , future , ")");
        return 1;
    }
    future -= 5;

    G_UI->PrintLog(name, "의 특성 '뒤엎는 미래' 발동!");

    //(ATK / 3)만큼 HP 회복
    HP += ATK / 3;
    G_UI->PrintLog( name , "은(는) ATK(" , ATK , ") / 3만큼 HP 회복 → HP: " , HP);

    //(최근 데미지 / 3) 만큼 회복량 기준 보너스 결정
    int bonusHeal = (lastDamage / 3);
    HP += bonusHeal;
    G_UI->PrintLog( "최근 데미지(" , lastDamage , ") / 3 = " , bonusHeal , " 추가 회복 → HP: " , HP);

    //회복 후 HP 구간별 MP, 미래 스택 증가
    if (HP < 22) {
        MP += 3;
        G_UI->PrintLog("MP +3 획득! (MP: " , MP , ")");
    }
    else if (HP < 25) {
        MP += 3;
        future += 1;
        G_UI->PrintLog("MP +3, 미래 +1 획득! (MP: " , MP , ", 미래: " , future , ")");
    }
    else {
        MP += 5;
        future += 2;
        G_UI->PrintLog( "MP +5, 미래 +2 획득! (MP: " , MP , ", 미래: " , future , ")");
    }
    return 0;
}

int Boss::heavensDoor(Player& player) {
    // MP 8 소모
    if (MP < 8) {
        //G_UI->PrintLog(name , " : MP가 부족합니다. (필요:8, 현재:" , MP , ")");
        return 1;
    }
    MP -= 8;

    // (최근 피해 * 1.6) / 2 만큼 플레이어에게 데미지
    if (lastDamage < 1) {
        lastDamage = player.ATK;
    }

    int dmgValue = static_cast<int>((lastDamage * 1.6) / 2);
    player.HP -= dmgValue;
    player.hitDamage += dmgValue;
    G_UI->PrintLog( name , "은(는) '헤븐즈 도어'를 시전했다!");
    G_UI->PrintLog(player.name , "에게 " , dmgValue , "만큼의 피해를 입혔다.");

    // 미래 스택 +1
    future += 1;
    G_UI->PrintLog( "미래 스택 +1 (현재: " , future , ")");

    // 방금 입힌 피해를 lastDamage에 저장
    lastDamage = dmgValue;
    return 0;
}

int Boss::otherworldlyBlade(Player& player) {
    // MP 5 소모
    if (MP < 5) {
        //G_UI->PrintLog( name , " : MP가 부족합니다. (필요:5, 현재:" , MP , ")");
        return 1;
    }
    // 현재 HP의 10% 소모
    int hpCost = static_cast<int>(HP * 0.1);
    HP -= hpCost;
    MP -= 5;

    G_UI->PrintLog( name , "은(는) ‘이계의 검’을 시전하며 HP ", hpCost , "를 희생했다! (남은 HP: " , HP , ")");

    // (최근데미지 ×1.4) / 3 만큼 플레이어에게 피해
    int dmgValue = static_cast<int>((lastDamage * 1.4) / 3);
    player.HP -= dmgValue;
    player.hitDamage += dmgValue;
    G_UI->PrintLog( player.name , "에게 " , dmgValue , "만큼의 피해를 입혔다!");

    // ATK+2, DEF+1
    ATK += 2;
    DEF += 1;
    G_UI->PrintLog(name , "의 공격력 ATK +2, 방어력 DEF +1 영구 증가! " , "(ATK: " , ATK , ", DEF: " , DEF , ")");

    // 최근 데미지 기록 갱신
    lastDamage = dmgValue;
    return 0;
}

//미래스택반환 UI에서 사용
int Boss::Get_Stack()
{
    return future;
}
Monster slime("슬라임", 24, 0, 5, 7);
Monster king_slime("킹슬라임", 37, 0, 8, 11);
Monster watterrat("워터렛", 49, 5, 11, 15);
Monster chandelier("샹들리에", 61, 6, 13, 18);
Boss witch("마녀", 200, 7, 14, 20, 6);

std::map<int, Monster*> monsterMap = createMonsterMap();

//가동용 더미
Monster zero("더미", 0, 0, 0, 0);
