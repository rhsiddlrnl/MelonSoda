#include "Player.h"
#include <iostream>
#include <algorithm>
#include "Monster.h"

Player::Player(std::string player_name) {
	name = player_name;
	HP = 100;
	MP = 10;
	ATK = 10;
	DEF = 5;

	//참기 초기화
	concentration = 0;
	//최근 공격력 데미지 초기화
	lastDamage = 0;
	//1턴 동안 데미지 감소 상태 여부 초기화
	isReflecting = false;
}

void Player::showPStat() {
	std::cout << "Name : " << name << std::endl;
	std::cout << "HP : " << HP << std::endl;
	std::cout << "MP : " << MP << std::endl;
	std::cout << "ATK : " << ATK << std::endl;
	std::cout << "DEF : " << DEF << std::endl;
	std::cout << "concentration : " << concentration << std::endl;
}

void Player::showInventory() {
	int num = 1;
	//과일하고 음료수 둘 다 하나이상 보유시에만 표시용
	if (!fruit_inventory.empty()) {
		std::cout << "---과일 주머니---" << std::endl;
		for (const auto& item : fruit_inventory) {
			std::cout << num++ << " " << item.name << std::endl;
		}
	}
	
	if (!drink_inventory.empty()) {
		std::cout << "---마신 음료수---" << std::endl;
		for (const auto& item : drink_inventory) {
			std::cout << item.name << std::endl;
		}
	}
}

void Player::addInventory(FRUIT fruit) {
	fruit_inventory.push_back(fruit);
	std::cout << fruit.name << "을(를) 획득했다!" << std::endl;

	HP += fruit.HP;
	MP += fruit.MP;
	ATK += fruit.ATK;
	DEF += fruit.DEF;

	std::cout << fruit.name << "을(를) 주머니에 넣었다. ";
	if (fruit.HP != 0) std::cout << "체력이 " << fruit.HP << " ";
	if (fruit.MP != 0) std::cout << "마나가 " << fruit.MP << " ";
	if (fruit.ATK != 0) std::cout << "공격력이 " << fruit.ATK << " ";
	if (fruit.DEF != 0) std::cout << "방어력이 " << fruit.DEF << " ";
	std::cout << "만큼 변화했다." << std::endl;
}

void Player::useInventory(FRUIT fruit) {
	auto it = std::find(fruit_inventory.begin(), fruit_inventory.end(), fruit);
	if (it != fruit_inventory.end()) {
		std::cout << it->name << "의 효과가 사라졌다." << std::endl;
		HP -= it->HP;
		MP -= it->MP;
		ATK -= it->ATK;
		DEF -= it->DEF;

		//if (fruit.HP != 0) std::cout << "체력이 " << it->HP << " ";
		//if (fruit.MP != 0) std::cout << "마나가 " << it->MP << " ";
		//if (fruit.ATK != 0) std::cout << "공격력이 " << it->ATK << " ";
		//if (fruit.DEF != 0) std::cout << "방어력이 " << it->DEF << " ";
		//std::cout << "감소했다." << std::endl;

		fruit_inventory.erase(it);
	}
	else {
		std::cout << "해당 아이템이 없습니다." << std::endl;
	}
}

//연산자 중복이드래요~
void Player::blendFruit(FRUIT fruit1, FRUIT fruit2) {
	useInventory(fruit1);
	useInventory(fruit2);
	DRINK temp;
	temp = fruit1 + fruit2;
	addDrink(temp);
}

void Player::addDrink(DRINK drink)
{
	drink_inventory.push_back(drink);
	std::cout << drink.name << "을(를) 만들었다!" << std::endl;

	HP += drink.HP;
	MP += drink.MP;
	ATK += drink.ATK;
	DEF += drink.DEF;

	std::cout << drink.name << "을(를) 마셨다. ";
	if (drink.HP != 0) std::cout << "체력이 " << drink.HP << " ";
	if (drink.MP != 0) std::cout << "마나가 " << drink.MP << " ";
	if (drink.ATK != 0) std::cout << "공격력이 " << drink.ATK << " ";
	if (drink.DEF != 0) std::cout << "방어력이 " << drink.DEF << " ";
	std::cout << "증가했다!" << std::endl;
}

//참기 구현 함수
void Player::addConcentration() {
	concentration++;
	ATK += 2;
	DEF += 2;
	MP += 2;
	std::cout << "참기를 모았다! 현재 참기: " << concentration << std::endl;
	std::cout << "공격력, 방어력, 마나가 각각 2씩 증가했다!" << std::endl;
}

//플레이어 스킬 사용 함수
void Player::useSkill(Monster& monster) {
	int skillChoice;
	std::cout << "\n[스킬 목록]\n";
	std::cout << "1. 소드 오러 (참기 3, MP 4)\n";
	std::cout << "   - 최근 공격의 1.4배 피해 + 피해의 절반만큼 HP 회복\n";

	std::cout << "2. 베기 (MP 3)\n";
	std::cout << "   - 최근 공격의 1.3배 피해 + 참기 +1\n";

	std::cout << "3. 튕겨내기 (MP 4)\n";
	std::cout << "   - 1턴 동안 받는 데미지 30% 감소 + 참기 +1\n";

	std::cout << "4. 릴리즈 (참기 2, MP 4)\n";
	std::cout << "   - (현재 HP × 0.1) × 현재 참기 스택만큼 피해\n";

	std::cout << "스킬 번호를 입력하세요: ";
	std::cin >> skillChoice;

	switch (skillChoice) {
	case 1:
		swordOrder(monster);
		break;
	case 2:
		slash(monster);
		break;
	case 3:
		reflect();
		break;
	case 4:
		release(monster);
		break;
	default:
		std::cout << "잘못된 선택입니다.\n";
		break;
	}
}

//플레이어 소드오러 스킬 함수
void Player::swordOrder(Monster& monster) {
	if (concentration < 3) {
		std::cout << "참기가 부족합니다. (필요: 3, 현재: " << concentration << ")\n";
		return;
	}
	if (MP < 4) {
		std::cout << "마나가 부족합니다. (필요: 4, 현재: " << MP << ")\n";
		return;
	}

	MP -= 4;
	concentration -= 3;

	int damage = static_cast<int>(lastDamage * 1.4);
	monster.HP -= damage;
	int heal = damage / 2;
	HP += heal;

	std::cout << "\n[소드 오러 스킬 사용]\n";
	std::cout << "- " << monster.name << "에게 " << damage << " 데미지를 입혔다.\n";
	std::cout << "- 피해의 절반(" << heal << ") 만큼 HP를 회복했다.\n";
}

//플레이어 베기 스킬 함수
void Player::slash(Monster& monster) {
	if (MP < 3) {
		std::cout << "마나가 부족합니다. (필요: 3, 현재: " << MP << ")\n";
		return;
	}

	MP -= 3;

	//기본 공격 없을 땐 초기 공격력 사용
	int baseDamage = (lastDamage > 0) ? lastDamage : ATK;
	int estimated = static_cast<int>(baseDamage * 1.3);

	// 실제 데미지 계산식에 따라 처리
	int att = estimated;
	int def = monster.DEF;
	int damage = (att * 100) / (def + 100);

	monster.HP -= damage;

	// 참기 1 증가 및 능력치 상승
	concentration++;
	ATK += 2;
	DEF += 2;
	MP += 2;

	std::cout << "\n[베기 스킬 사용]\n";
	std::cout << "- " << monster.name << "에게 " << damage << " 데미지를 입혔다.\n";
	if (lastDamage == 0) {
		std::cout << "- 최근 공격 기록 없음 → 기본 공격력(" << baseDamage << ") 기준으로 계산\n";
	}
	std::cout << "- 참기를 모았다! 현재 참기: " << concentration << ", 공격력, 방어력, 마나가 각각 2씩 증가했다!\n";
}

//플레이어 튕겨내기 스킬
void Player::reflect() {
	if (MP < 4) {
		std::cout << "마나가 부족합니다. (필요: 4, 현재: " << MP << ")\n";
		return;
	}

	MP -= 4;
	concentration++;
	ATK += 2;
	DEF += 2;
	MP += 2;

	isReflecting = true;  //이 턴 동안 데미지 감소 적용

	std::cout << "\n[튕겨내기 스킬 사용]\n";
	std::cout << "- 몬스터의 다음 공격 피해가 30% 감소됩니다.\n";
	std::cout << "- 참기 스택 +1 (현재: " << concentration << "), ATK/DEF/MP +2\n";
}

//플레이어 릴리즈 스킬
void Player::release(Monster& monster) {
	if (concentration < 2) {
		std::cout << "참기가 부족합니다. (필요: 2, 현재: " << concentration << ")\n";
		return;
	}
	if (MP < 4) {
		std::cout << "마나가 부족합니다. (필요: 4, 현재: " << MP << ")\n";
		return;
	}

	MP -= 4;

	// ((플레이어의 현재 hp) x 0.1) x (참기 스택)
	int damage = static_cast<int>((HP * 0.1) * concentration);
	monster.HP -= damage;

	// 참기 2 소모
	concentration -= 2;

	std::cout << "\n[릴리즈 스킬 사용]\n";
	std::cout << "- 현재 HP의 10% × 참기 스택을 피해로 전환!\n";
	std::cout << "- " << monster.name << "에게 " << damage << " 데미지를 입혔다.\n";
	std::cout << "- 참기 스택 2가 소모되었습니다. (현재: " << concentration << ")\n";
}