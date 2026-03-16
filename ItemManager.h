#pragma once
#include "Item.h"
#include "MyVector.h"
#include "MyString.h"
#include "SlotAndVector.h" 
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>   
#include <cstring>  
#include <cstdlib>  

struct ItemManager {
    SlotAndVector allItems[7];
    MyString itemsFilePath;
    ItemManager(const MyString& filePath = "Items.txt");
    bool loadItemsFromTXT();
    MyVector<Item> getRandomItemChoices(int count, const bool* excludedSlots = nullptr);
    Item generateRandomFoundItem();
    const MyVector<Item>& getItemBySlot(SlotType slot) const;

    void printAllItems() const;
    int getTotalItemCount() const;

    bool isLoaded() const;
};
