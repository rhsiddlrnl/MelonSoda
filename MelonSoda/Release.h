#pragma once
#include "Skill.h"

class Release : public Skill {
public:
    std::string name() const override { return "릴리즈 (참기 2, MP 4)"; }
    std::string description() const override {
        return "(현재 HP × 0.1) × 현재 참기 스택만큼 피해";
    }
    int execute(Player& player, Monster& monster) override;
};