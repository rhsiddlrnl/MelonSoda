#pragma once
#include "Skill.h"

class SwordOrder : public Skill {
public:
    std::string name() const override { return "소드 오러 (참기 3, MP 4)"; }
    std::string description() const override {
        return "최근 공격의 1.4배 피해 + 피해의 절반만큼 HP 회복";
    }
    int execute(Player& player, Monster& monster) override;
};