#pragma once
#include "Actor.h"
#include "Fruit.h"
#include <vector>
#include "Monster.h"

//�÷��̾�� �⺻���� ���
//�߰��� ��: �κ��丮, ���丮 ��ȣ(���丮 ������� ��¿�), �����ڿ� �̸� �Ű������� ����(�����ϴ� ����� �Է���), �������� �Լ���
class Player : public Actor {
public:
	std::vector<FRUIT> fruit_inventory;
	std::vector<DRINK> drink_inventory;
	int story_index;

	//�÷��̾� �⺻���� �� ����
	int concentration;
	//�ֱ� ���� �������� ����
	int lastDamage;
	//1�� ���� ������ ���� ���� ����
	bool isReflecting;

	Player(std::string player_name);

	//�÷��̾� ���� �����ִ� �Լ�
	void showPStat();
	//�÷��̾� �κ��丮 �����ִ� �Լ�
	void showInventory();
	//�÷��̾� �κ��丮�� ���� �߰��ϴ� �Լ�
	void addInventory(FRUIT fruit);
	//�÷��̾� �κ��丮���� ���� �����ϴ� �Լ�
	void useInventory(FRUIT fruit);
	//BLEND!
	void blendFruit(FRUIT fruit1, FRUIT fruit2);
	//�÷��̾� �κ��丮�� ����� �߰��ϴ� �Լ�
	void addDrink(DRINK drink);
	//�÷��̾� ���� �Լ�
	void addConcentration();
	// ��ų �޴� �Լ�
	void useSkill(Monster& monster);
	// �ҵ� ���� ��ų
	void swordOrder(Monster& monster);
	// ���� ��ų
	void slash(Monster& monster);
	//ƨ�ܳ��� ��ų
	void reflect();
	// ������ ��ų
	void release(Monster& monster);
};