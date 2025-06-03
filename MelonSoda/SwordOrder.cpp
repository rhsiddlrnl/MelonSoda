#include "SwordOrder.h"
#include "Player.h"
#include "Monster.h"
#include "UIManager.h"

#include <iostream>

int SwordOrder::execute(Player& player, Monster& monster) {
    if (player.concentration < 3) {
        G_UI->PrintLog("참기가 부족합니다. (필요:3, 현재: ", player.concentration, ")");
        return 1;
    }
    if (player.MP < 4) {
        G_UI->PrintLog( "마나가 부족합니다. (필요:4, 현재: ", player.MP, ")");
        return 1;
    }
    player.MP -= 4;
    player.concentration -= 3;

    int damage = static_cast<int>(player.lastDamage * 1.4);
    monster.HP -= damage;
    monster.hitDamage += damage;
    int heal = damage / 2;
    player.HP += heal;

    G_UI->PrintLog("");
    G_UI->PrintLog( "[소드 오러 스킬 사용]" );
    G_UI->PrintLog(monster.name, "에게 ", damage , " 데미지를 입혔다.");
    G_UI->PrintLog("피해의 절반(" , heal , ") 만큼 HP를 회복했다.");
    return 0;
}