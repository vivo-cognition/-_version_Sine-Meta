#pragma once
#include "MyString.h"
#include "MyVector.h"
#include "Path.h"
#include "Player.h"
struct Mission {
    MyString name;
    MyString description;
    MyString secondDescription;
    MyString targetLocation;
    MyVector<Path> paths;

    Mission(const MyString& n = "Пусто", const MyString& desc = "Нет описания", const MyString& sdesc="Нет описания");
    MyString getName() const;
    MyString getDescription() const;
    MyVector <MyString> getAllNamePath();
    MyString FailOrWin(Player player, int selected);

    bool checkPath(const Player& player, int pathIdx);
};

