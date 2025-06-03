#include "Release.h"
#include "Player.h"
#include "Monster.h"
#include "UIManager.h"

#include <iostream>

int Release::execute(Player& player, Monster& monster) {
    if (player.concentration < 2) {
        G_UI->PrintLog( "참기가 부족합니다. (필요:2, 현재:" , player.concentration, ")");
        return 1;
    }
    if (player.MP < 4) {
        G_UI->PrintLog( "마나가 부족합니다. (필요:4, 현재:" , player.MP, ")");
        return 1;
    }
    player.MP -= 4;
    // ((플레이어의 현재 hp) x 0.1) x (참기 스택)
    int damage = static_cast<int>((player.HP * 0.1) * player.concentration);
    monster.HP -= damage;
    monster.hitDamage += damage;
    player.concentration -= 2;

    G_UI->PrintLog("[릴리즈 스킬 사용]");
    G_UI->PrintLog("- 현재 HP의 10% × 참기 스택을 피해로 전환!");
    G_UI->PrintLog("- " , monster.name , "에게 " , damage , " 데미지를 입혔다.");
    G_UI->PrintLog( "- 참기 스택 2가 소모되었습니다. (현재: " , player.concentration, ")");
    return 0;
}