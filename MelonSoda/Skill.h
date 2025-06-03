#pragma once
#include <string>

class Player;
class Monster;

class Skill {
public:
    virtual ~Skill() = default;
    // 스킬 실행
    virtual int execute(Player& player, Monster& monster) = 0;
    // 메뉴 출력용 이름/설명
    virtual std::string name() const = 0;
    virtual std::string description() const = 0;
};
