#define _CRT_SECURE_NO_WARNINGS
#include "ItemManager.h"
#include <iostream>

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
/*

	
	std::ifstream file(itemsFilePath);
	if (!file.is_open()) {
		std::cerr << "ОШИБКА: Файл не открывается'" << itemsFilePath << "'" << std::endl;
		return false;
	}
	try {
		json j;
		file >> j;

		if (!j.contains("items") || !j["items"].is_array()) {
			std::cerr << "ОШИБКА: Некорректная структура JSON файла" << std::endl;
			return false;
		}

		//обработка каждого предмета
		int loadedCount = 0;
		for (const auto& itemJson : j["items"]) {
			try {
				std::string name = itemJson["name"];
				std::string description = itemJson["description"];
				std::string slotTypeStr = itemJson["slotType"];

				SlotType slotType = Item::stringToSlotType(slotTypeStr);

				//чтение характеристик
				std::map<std::string, int> stats;
				if (itemJson.contains("stats") && itemJson["stats"].is_object()) {
					for (const auto& [statName, value] : itemJson["stats"].items()) {
						stats[statName] = value;
					}
				}

				//создание предмета и добавления в соответствующую категорию
				Item newItem(name, description, slotType, stats, false);
				allItems[slotType].push_back(newItem);
				loadedCount++;
			}
			catch (const json::exception& e) {
				std::cerr << "Предупреждение: ошибка чтения предмета - " << e.what() << std::endl;
				continue;
			}
		}

		std::cout << "Успешно загружено" << loadedCount << " предметов" << std::endl;
		return true;
	}
	catch (const json::exception& e) {
		std::cerr << "ОШИБКА парсинга JSON: " << e.what() << std::endl;
		return false;
	}
}

//Получить случайный предмет
std::vector<Item> ItemManager::getRandomItemChoices(int count,
	const std::set<SlotType>& excludedSlots) {
	std::vector<Item> choices;
	std::vector<SlotType> availableSlots;

	//Собираем доступные слоты
	for (const auto& [slotType, items] : allItems) {
		if (excludedSlots.find(slotType) == excludedSlots.end() && !items.empty()) {
			availableSlots.push_back(slotType);
		}
	}

	if (availableSlots.empty()) {
		std::cout << "Нет доступных предметов для выбора" << std::endl;
		return choices;
	}

	//Генератор случайных чисел
	std::random_device rd;
	std::mt19937 gen(rd());

	//перемешиваем достуупные слоты
	std::shuffle(availableSlots.begin(), availableSlots.end(), gen);
	 
	//Выбор предмета
	for (int i = 0;i < count && i < availableSlots.size();i++) {
		SlotType selectedSlot = availableSlots[i];

		if (!allItems[selectedSlot].empty()) {
			std::uniform_int_distribution<> itemDist(0,
				allItems[selectedSlot].size() - 1);
			choices.push_back(allItems[selectedSlot][itemDist(gen)]);
		}
	}
	return choices;
}

//Генерация найденного предмета
Item ItemManager::generateRandomFoundItem() {
	std::random_device rd;
	std::mt19937 gen(rd());

	if (!allItems.empty()) {
		return Item("Ничего", "Пустой предмет", SlotType::NONE);
	}

	//выбор случайного слота
	std::vector<SlotType> allSlotTypes;
	for (const auto& [slotType, _] : allItems) {
		if (!allItems[slotType].empty()) {
			allSlotTypes.push_back(slotType);
		}
	}

	if (allSlotTypes.empty()) {
		return Item();
	}

	std::uniform_int_distribution<> slotDist(0, allSlotTypes.size() - 1);
	SlotType randomSlot = allSlotTypes[slotDist(gen)];

	//выбор случайного предмета из этого слота
	std::uniform_int_distribution<> itemDist(0, allItems[randomSlot].size() - 1);

	Item foundItem = allItems[randomSlot][itemDist(gen)];

	//создание копии с пометкой найденный
	return Item(foundItem.getName() + "(найденный)",
		"Вы нашли этот предмет по пути",
		foundItem.getSlotType(),
		foundItem.getStats(),
		true);
}

//Получить все предметы определенного типа
const std::vector<Item>& ItemManager::getItemsBySlot(SlotType slot) const {
	static const std::vector<Item> emptyVector;
	auto it = allItems.find(slot);
	if (it != allItems.end()) {
		return it -> second;
	}
	return emptyVector;
}

//Получить все предметы
const std::map<SlotType, std::vector <Item>>& ItemManager::getAllItems() const {
	return allItems;
}

//Вывести все предметы
void ItemManager::printAllItems() const {
	if (allItems.empty()) {
		std::cout << "Нет загруженных предметов" << std::endl;
		return;
	}
	
	std::cout << "\n=== ВСЕ ПРЕДМЕТЫ ===" << std::endl;
	for (const auto& [slotType, items] : allItems) {
		std::cout << "\n[" << Item::slotTypeToString(slotType)
			<< "]-" << items.size() << " предметов:" << std::endl;

		for (const auto& item : items) {
			std::cout << " ~ " << item.getName();
			std::cout << " - " << item.getDescription() << std::endl;

			//вывод характеристик
			const auto& stats = item.getStats();
			if (!stats.empty()) {
				std::cout << "Характеристики: ";
				for (const auto& [stat, value] : stats) {
					std::cout << stat << ": " << value<<" ";
				}		
				std::cout << std::endl;		
			}		
		}
	}
	std::cout << "===============\n" << std::endl;
}	

//получить общее количество предметов
int ItemManager::getTotalItemCount() const {
		int count = 0;
		for (const auto& [_, items] : allItems) {
			count += items.size();
		}
		return count;
	}

	//здесь будет крутая программа*/