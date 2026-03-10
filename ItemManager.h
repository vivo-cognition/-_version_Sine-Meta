#pragma once
#include "Item.h"
#include "ItemVector.h"
#define _CRT_SECURE_NO_WARNINGS
#include "SlotAndVector.h"
#include "MyString.h"
#include <cstdio>   
#include <cstring>  
#include <cstdlib>  

struct ItemManager {
    SlotAndVector allItems[7];
    MyString itemsFilePath;

    ItemManager(const MyString& filePath = "Items.txt");

    bool loadItemsFromTXT();

    ItemVector getRandomItemChoices(int count, const bool* excludedSlots = nullptr);
    Item generateRandomFoundItem();

    const ItemVector& getItemBySlot(SlotType slot) const;

    void printAllItems() const;
    int getTotalItemCount() const;

    bool isLoaded() const;
};
