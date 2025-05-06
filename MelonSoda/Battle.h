#pragma once
#include "Monster.h"
#include "Player.h"
#include "Fruit.h"
#include <iostream>
#include <windows.h>

void Battle(Player& player, Monster& monster);
int dmg(Actor attacker, Actor defender);
void Event(Player& player, Monster& monster);
void afterBattle(Player& player);
