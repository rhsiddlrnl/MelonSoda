#pragma once
#include "Skill.h"
#include "SwordOrder.h"
#include "Slash.h"
#include "Reflect.h"
#include "Release.h"
#include <map>
#include <memory>

inline std::map<int, std::unique_ptr<Skill>> createSkillMap() {
    std::map<int, std::unique_ptr<Skill>> m;
    m[1] = std::make_unique<SwordOrder>();
    m[2] = std::make_unique<Slash>();
    m[3] = std::make_unique<Reflect>();
    m[4] = std::make_unique<Release>();
    return m;
}