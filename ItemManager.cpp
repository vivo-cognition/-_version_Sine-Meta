#define _CRT_SECURE_NO_WARNINGS
#include "ItemManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

ItemManager::ItemManager(const MyString& filePath)
	: itemsFilePath(filePath) {
	loadItemsFromTXT();
}

bool ItemManager::loadItemsFromTXT() {
	FILE* file = fopen(itemsFilePath.c_str(), "r");
	if (!file) return false;

	char line[256];
	while (fgets(line, sizeof(line), file)) {
		char slotName[50];
		int itemsInSlot = 0;

		if (sscanf(line, "%s %d", slotName, &itemsInSlot) >= 2) {
			SlotType currentSlot = Item::MyStringToSlotType(slotName);

			for (int i = 0; i < itemsInSlot; i++) {
				fgets(line, sizeof(line), file);
				line[strcspn(line, "\r\n")] = 0;
				MyString itemName = line;

				fgets(line, sizeof(line), file);
				line[strcspn(line, "\r\n")] = 0;
				MyString itemDesc = line;

				fgets(line, sizeof(line), file);
				line[strcspn(line, "\r\n")] = 0;
				MyString locTag = line;

				fgets(line, sizeof(line), file);
				int statsCount = atoi(line);
				StatVector itemStats(statsCount);

				for (int j = 0; j < statsCount; j++) {
					char sName[50];
					int sVal;
					fscanf(file, "%s %d\n", sName, &sVal);
					itemStats.setAt(j, MyString(sName), sVal);
				}

				Item newItem(itemName, itemDesc, currentSlot, itemStats, false, locTag);
				allItems[(int)currentSlot].items.push_back(newItem);
			}
		}
	}
	fclose(file);
	return true;
}

MyVector<Item> ItemManager::getRandomItemChoices(int count, ShopType shop) {
	MyVector<Item> choices;
	bool alreadyPickedInThisRoll[7] = { false };
	int safetyCounter = 0;
	while (choices.getSize() < count && safetyCounter < 200) {
		safetyCounter++;
		int targetSlot = -1;
		int roll = rand() % 100;
		switch (shop) {
		case FOREIGNER:
			if (roll < 50) targetSlot = NONE;
			else if (roll < 80) targetSlot = SPECIAL;
			else targetSlot = rand() % 5;
			break;
		case MAIDEN:
			if (roll < 40) targetSlot = HEAD;
			else if (roll < 70) targetSlot = BODY;
			else targetSlot = NONE;
			break;
		case WITCH:
			if (roll < 50) targetSlot = SPECIAL;
			else if (roll < 80) targetSlot = WEAPON;
			else targetSlot = rand() % 4;
			break;
		case OLD_MAN:
			if (roll < 40) targetSlot = WEAPON;
			else targetSlot = rand() % 4;
			break;
		}
		if (targetSlot != -1 && allItems[targetSlot].items.getSize() > 0) {
			if (alreadyPickedInThisRoll[targetSlot]) {
				if (rand() % 100 > 20) continue;
			}
			int itemsCount = allItems[targetSlot].items.getSize();
			Item foundItem = allItems[targetSlot].items[rand() % itemsCount];

			bool isDuplicate = false;
			for (int i = 0; i < choices.getSize(); i++) {
				if (choices[i].getName() == foundItem.getName()) {
					isDuplicate = true;
					break;
				}
			}

			if (!isDuplicate) {
				choices.push_back(foundItem);
				alreadyPickedInThisRoll[targetSlot] = true;
			}
		}
	}
	return choices;
}
Item ItemManager::generateRandomFoundItem(MyString tag) {
	int noneIdx = (int)SlotType::NONE;
	MyVector<int> possibleIndices;
	for (int i = 0; i < allItems[noneIdx].items.getSize(); ++i) {
		Item& item = allItems[noneIdx].items[i];
		if (!item.isFound() && (item.locationType == tag || item.locationType == "Globale")) {
			possibleIndices.push_back(i);
		}
	}

	if (possibleIndices.getSize() == 0) {
		return Item("Ничего", "Тут больше нечего искать.", SlotType::NONE);
	}

	int randomIndex = possibleIndices[rand() % possibleIndices.getSize()];
	Item& baseItem = allItems[noneIdx].items[randomIndex];

	baseItem.isFoundItem = true;

	return Item(baseItem.getName(), baseItem.getDescription(), SlotType::NONE, baseItem.getStats(), true, baseItem.locationType);
}



const MyVector<Item>& ItemManager::getItemBySlot(SlotType slot) const {
	int idx = (int)slot;
	if (idx < 0 || idx >= 7) {
		return allItems[0].items;
	}
	return allItems[idx].items;
}

void ItemManager::printAllItems() const {
	if (getTotalItemCount() == 0) {
		std::cout << "Нет загруженных предметов" << std::endl;
		return;
	}
	std::cout << "\n=== ВСЕ ПРЕДМЕТЫ В БАЗЕ ===" << std::endl;
	for (int i = 0; i < 7; i++) {
		const MyVector<Item>& currentItems = allItems[i].items;
		if (currentItems.getSize() == 0) continue;
		std::cout << "\n[" << Item::SlotTypeToMyString((SlotType)i).c_str()
			<< "] - " << currentItems.getSize() << " предметов:" << std::endl;
		for (int j = 0; j < currentItems.getSize(); j++) {
			const Item& item = currentItems[j];
			std::cout << " ~ " << item.getName().c_str();
			std::cout << " - " << item.getDescription().c_str() << std::endl;
			const StatVector& stats = item.getStats();
			if (!stats.empty()) {
				std::cout << "   Характеристики: ";
				for (int k = 0; k < stats.size; k++) {
					StatPair pair = stats.getAt(k);
					std::cout << pair.key.c_str() << ": " << pair.value << "  ";
				}
				std::cout << std::endl;
			}
		}
	}
	std::cout << "\n===========================\n" << std::endl;
}

int ItemManager::getTotalItemCount() const {
	int total = 0;
	for (int i = 0; i < 7; i++) {
		total += allItems[i].items.getSize();
	}
	return total;
}

bool ItemManager::isLoaded() const {
	return getTotalItemCount() > 0;
}

Item* ItemManager::findItemByName(const MyString& name) {
	for (int i = 0; i < 7; i++) {
		int count = allItems[i].items.getSize();
		for (int j = 0; j < count; j++) {
			if (allItems[i].items[j].getName() == name) {
				return &allItems[i].items[j];
			}
		}
	}
	return nullptr;
}
