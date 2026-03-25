#pragma once
#include "StatVector.h"
#include "MyString.h"
#include "Item.h"
#include "MyVector.h"

class Player {
private:
    MyString name;
    MyVector<Item> inventory;
    StatVector totalStats;

public:
    Player(const MyString& n);

    void equipItem(const Item& item);
    int getStatValue(const MyString& statName) const;
    void printStatus() const;
    void applyStatChange(const StatVector& rewards);
};
