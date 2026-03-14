#pragma once
#include "ItemVector.h"
#include "StatVector.h"
#include "MyString.h"
#include "Item.h"

class Player {
private:
    MyString name;
    ItemVector inventory;
    StatVector totalStats;

public:
    Player(const MyString& n);

    void equipItem(const Item& item);
    int getStatValue(const MyString& statName) const;
    void printStatus() const;
};
