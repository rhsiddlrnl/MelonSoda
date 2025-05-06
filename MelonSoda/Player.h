#pragma once
#include "Actor.h"
#include "Fruit.h"
#include <vector>

class Player : public Actor {
public:
	std::vector<FRUIT> fruit_inventory;
	std::vector<DRINK> drink_inventory;
	int story_index;

	Player(std::string player_name);

	void showPStat();
	void showInventory();
	void addInventory(FRUIT fruit);
	void useInventory(FRUIT fruit);
	void blendFruit(FRUIT fruit1, FRUIT fruit2);
	void addDrink(DRINK drink);
};
