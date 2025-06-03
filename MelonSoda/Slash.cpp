#include "Slash.h"
#include "Player.h"
#include "Monster.h"
#include "UIManager.h"

#include <iostream>

int Slash::execute(Player& player, Monster& monster) {
    if (player.MP < 3) {
        G_UI->PrintLog( "마나가 부족합니다. (필요:3, 현재:", player.MP, ")");
        return 1;
    }
    player.MP -= 3;
    int base = (player.lastDamage > 0 ? player.lastDamage : player.ATK);
    int est = static_cast<int>(base * 1.3);
    int damage = (est * 100) / (monster.DEF + 100);
    monster.HP -= damage;
    monster.hitDamage += damage;

    player.concentration++;
    player.ATK += 2;
    player.DEF += 2;
    player.MP += 2;

    G_UI->PrintLog( "[베기] " , monster.name , "에 " , damage, " 데미지, 참기+1 (현재: " , player.concentration, ")");
    return 0;
}