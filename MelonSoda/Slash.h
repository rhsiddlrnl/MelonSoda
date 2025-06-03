#pragma once
#include "Skill.h"

class Slash : public Skill {
public:
    std::string name() const override { return "베기 (MP 3)"; }
    std::string description() const override {
        return "최근 공격의 1.3배 피해 + 참기 +1";
    }
    int execute(Player& player, Monster& monster) override;
};