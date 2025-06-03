#pragma once
#include "Skill.h"

class Reflect : public Skill {
public:
    std::string name() const override { return "튕겨내기 (MP 4)"; }
    std::string description() const override {
        return "1턴 동안 받는 데미지 30% 감소 + 참기 +1";
    }
    int execute(Player& player, Monster& monster) override;
};