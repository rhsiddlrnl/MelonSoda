#include "Reflect.h"
#include "Player.h"
#include "Monster.h"
#include "UIManager.h"

#include <iostream>

int Reflect::execute(Player& player, Monster& monster) {
    if (player.MP < 4) {
        G_UI->PrintLog("마나가 부족합니다. (필요:4, 현재:", player.MP, ")");
        return 1;
    }
    player.MP -= 4;
    player.concentration++;
    player.ATK += 2;
    player.DEF += 2;
    player.MP += 2;

    player.isReflecting = true;
    G_UI->PrintLog("");
    G_UI->PrintLog( "[튕겨내기 스킬 사용]");
    G_UI->PrintLog("- 몬스터의 다음 공격 피해가 30% 감소됩니다.");
    G_UI->PrintLog("- 참기 스택 +1 (현재: " , player.concentration , "), ATK/DEF/MP +2");

    return 0;
}