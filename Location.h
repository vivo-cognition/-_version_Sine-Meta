#pragma once
#include <iostream>
#include "Player.h"
#include "MyString.h"
#include "StatVector.h"

struct Location {
    MyString name;
    MyString description;
    StatVector requirements;
    MyString successText;
    MyString failText;

    Location(const MyString& n = "Ничего",
        const MyString& desc = "Нет описания",
        const StatVector& initialStats = StatVector(0),
        const MyString& s = "Ничего",
        const MyString& f = "Нет описания");
    MyString getName() const;
    MyString getDescription() const;

    bool checkVictory(const Player&);
};