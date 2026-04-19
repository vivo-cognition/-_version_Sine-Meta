#pragma once
#include <iostream>
#include "Player.h"
#include "MyString.h"
#include "StatVector.h"
#include "path.h"
#include "MyVector.h"

struct Location {
    MyString name;
    MyString description;
    MyVector<Path> paths;

    Location(const MyString& n = "Пусто", const MyString& desc = "Нет описания");
    MyString getName() const;
    MyString getDescription() const;
    MyVector <MyString> getAllNamePath();
    MyString FailOrWin(Player player, int selected);

    bool checkPath(const Player& player, int pathIdx);
};