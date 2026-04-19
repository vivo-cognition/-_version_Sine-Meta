#pragma once
#include "StatVector.h"
#include "MyString.h"
#include "Item.h"
#include "MyVector.h"

struct Player {
    MyString name;
    MyString desc;
    MyVector<Item> inventory;
    StatVector totalStats;

    Player(const MyString& n="»грок", const MyString& d="кто-то");
    Player(const MyString& n, const MyString& d, const StatVector& s);

    void equipItem(const Item& item);
    void unEquipItem(const Item& item);
    Item findItemInSlot(SlotType targetSlotType);
    MyVector <MyString> getItemsBySlot(SlotType targetSlotType);
    void printStatus() const;
    void applyStatChange(const StatVector& rewards);
    bool canPassRequirements(const StatVector& requirements) const;


    const MyString& getName() const { return name; }
    const MyVector<Item>& getInventory() const { return inventory; }
    const StatVector& getStats() const { return totalStats; }
    int getStatValue(const MyString& statName) const;
};
