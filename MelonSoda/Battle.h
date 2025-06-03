#pragma once
#include "Monster.h"
#include "Player.h"
#include "Fruit.h"
#include <iostream>
#include <windows.h>
#include <map>

void Battle(Player& player, Monster& monster);
int dmg(Actor attacker, Actor defender);
void Event(Player& player, Monster& monster);
void afterBattle(Player& player);

void GAME(Player& player, const std::map<int, Monster*>& monsterMap);