#define _CRT_SECURE_NO_WARNINGS
#include "ItemManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

ItemManager::ItemManager(const MyString& filePath)
	: itemsFilePath(filePath) {
	loadItemsFromTXT();
}
bool ItemManager::loadItemsFromTXT() {
	for (int i = 0; i < 7; i++) {
		allItems[i].items.clear();
		allItems[i].slot = (SlotType)i;
	}
	std::cout << "Загрузка предметов из файла: " << itemsFilePath << std::endl;
	FILE* file = fopen(itemsFilePath.c_str(), "r");
	if (!file) {
		printf("ОШИБКА: Файл %s не найден\n", itemsFilePath.c_str());
		return false;
	}
	char line[256];
	int loadedCount = 0;
	while (fgets(line, sizeof(line), file)) {
		char slotName[50];
		int itemsInSlot = 0;
		if (sscanf(line, "%s %d {", slotName, &itemsInSlot) == 2) {
			SlotType currentSlot = Item::MyStringToSlotType(slotName);

			for (int i = 0; i < itemsInSlot; i++) {
				fgets(line, sizeof(line), file);

				fgets(line, sizeof(line), file);
				line[strcspn(line, "\n")] = 0;
				MyString itemName = line;

				fgets(line, sizeof(line), file);
				line[strcspn(line, "\n")] = 0;
				MyString itemDesc = line;

				int statsCount = 0;
				fgets(line, sizeof(line), file);
				statsCount = atoi(line);

				StatVector itemStats(statsCount);

				for (int j = 0; j < statsCount; j++) {
					char statName[50];
					int statValue;
					fscanf(file, "%s %d\n", statName, &statValue);
					itemStats.setAt(j, MyString(statName), statValue);
				}

				Item newItem(itemName, itemDesc, currentSlot, itemStats, false);
				allItems[(int)currentSlot].items.push_back(newItem);
				loadedCount++;
			}
		}
	}
	fclose(file);
	printf("Успешно загружено %d предметов\n", loadedCount);
	return true;
}
ItemVector ItemManager::getRandomItemChoices(int count, const bool* excludedSlots) {
	ItemVector choices;
	bool alreadyPickedInThisRoll[7] = { false };
	int availableSlotsCount = 0;
	for (int i = 0; i < 7; i++) {
		if ((excludedSlots == nullptr || !excludedSlots[i]) && allItems[i].items.getSize() > 0) {
			availableSlotsCount++;
		}
	}
	if (count > availableSlotsCount) {
		count = availableSlotsCount;
	}
	int attempts = 0;
	while (choices.getSize() < count && attempts < 200) {
		attempts++;
		srand(time(NULL));
		int randomSlotIdx = rand() % 7;
		bool isExcluded = (excludedSlots != nullptr && excludedSlots[randomSlotIdx]);
		bool isAlreadyPicked = alreadyPickedInThisRoll[randomSlotIdx];
		bool isEmpty = (allItems[randomSlotIdx].items.getSize() == 0);
		if (!isExcluded && !isAlreadyPicked && !isEmpty) {
			int itemsInSlot = allItems[randomSlotIdx].items.getSize();
			int randomItemIdx = rand() % itemsInSlot;

			Item foundItem = allItems[randomSlotIdx].items.getAt(randomItemIdx);
			choices.push_back(foundItem);
			alreadyPickedInThisRoll[randomItemIdx] = true;
		}
	}
	return choices;
}
Item ItemManager::generateRandomFoundItem() {
	int noneIdx = (int)SlotType::NONE;
	int count = allItems[noneIdx].items.getSize();
	if (count <= 0) {
		return Item("Ничего", "Вы обыскали всё, но ничего не нашли", SlotType::NONE);
	}
	int randomIdx = rand() % count;
	Item baseItem = allItems[noneIdx].items.getAt(randomIdx);
	return Item(baseItem.getName(), baseItem.getDescription(), SlotType::NONE, baseItem.getStats(), true);
}

const ItemVector& ItemManager::getItemBySlot(SlotType slot) const {
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
		const ItemVector& currentItems = allItems[i].items;
		if (currentItems.getSize() == 0) continue;
		std::cout << "\n[" << Item::SlotTypeToMyString((SlotType)i).c_str()
			<< "] - " << currentItems.getSize() << " предметов:" << std::endl;
		for (int j = 0; j < currentItems.getSize(); j++) {
			const Item& item = currentItems.getAt(j);
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
