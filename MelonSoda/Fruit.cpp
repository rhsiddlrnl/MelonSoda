#include "Fruit.h"

FRUIT::FRUIT(std::string fruit_name, int fruit_HP, int fruit_MP, int fruit_ATK, int fruit_DEF, int fruit_index) {
	name = fruit_name;
	HP = fruit_HP;
	MP = fruit_MP;
	ATK = fruit_ATK;
	DEF = fruit_DEF;
	Index = fruit_index;
}

bool FRUIT::operator==(const FRUIT& other) const {
	return name == other.name && Index == other.Index;
}

//����("�̸�", ü��, ����, ���ݷ�, ����, ������ȣ) ����� ��ȣ�� 1 2 4 8 16 32 64 128...�̷������� �ο��� ��
const FRUIT orange("������", 0, 0, 0, 0, 1);
const FRUIT apple("���",0, 0, 0, 0, 2);
const FRUIT grapefruit("�ڸ�", 0, 0, 0, 0, 4);
const FRUIT grape("����", 0, 0, 0, 0, 8);
const FRUIT avocado("�ƺ�ī��", 0, 0, 0, 0, 16);
const FRUIT watermelon("����", 0, 0, 0, 0, 32);

//�����("�̸�", ü��, ����, ���ݷ�, ����, ������ȣ) ����� ��ȣ�� ���� ������ȣ 2�������� 3 5 6 9 10 12...�̷������� �ο��� ��