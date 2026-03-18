#define _CRT_SECURE_NO_WARNINGS
#include "LocationManager.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

LocationManager::LocationManager(const MyString& filePath)
    : locationsFilePath(filePath) {
    loadLocationsFromTxt();
}

bool LocationManager::loadLocationsFromTxt() {
    allLocations.clear();

    std::cout << "Загрузка локаций из файла: " << locationsFilePath.c_str() << std::endl;
    FILE* file = fopen(locationsFilePath.c_str(), "r");
    if (!file) {
        printf("ОШИБКА: Файл %s не найден\n", locationsFilePath.c_str());
        return false;
    }

    char line[1024];
    int loadedCount = 0;
    while (fgets(line, sizeof(line), file)) {
        char locName[64];
        if (sscanf(line, "%s {", locName) == 1) {
            Location newLoc;
            newLoc.name = MyString(locName);
            if (fgets(line, sizeof(line), file)) {
                line[strcspn(line, "\r\n")] = 0;
                newLoc.description = MyString(line);
            }
            if (fgets(line, sizeof(line), file)) {
                int statsCount = atoi(line);
                StatVector locationStats(statsCount);
                for (int i = 0; i < statsCount; i++) {
                    if (fgets(line, sizeof(line), file)) {
                        char sName[64];
                        int sVal;
                        if (sscanf(line, "%s %d", sName, &sVal) == 2) {
                            locationStats.setAt(i, MyString(sName), sVal);
                        }
                    }
                }
                newLoc.requirements = locationStats;
            }
            if (fgets(line, sizeof(line), file)) {
                line[strcspn(line, "\r\n")] = 0;
                newLoc.successText = MyString(line);
            }
            if (fgets(line, sizeof(line), file)) {
                line[strcspn(line, "\r\n")] = 0;
                newLoc.failText = MyString(line);
            }
            fgets(line, sizeof(line), file);

            allLocations.push_back(newLoc);
            loadedCount++;
        }
    }

    fclose(file);
    printf("Успешно загружено %d локаций\n", loadedCount);
    return true;
}

const MyVector<Location>& LocationManager::getAllLocations() const {
    return allLocations;
}

int LocationManager::getTotalCount() const {
    return allLocations.getSize();
}

void LocationManager::printAllLocations() const {
    if (allLocations.getSize() == 0) {
        std::cout << "Нет загруженных локаций" << std::endl;
        return;
    }

    std::cout << "\n=== СПИСОК ДОСТУПНЫХ ЛОКАЦИЙ ===" << std::endl;

    for (int i = 0; i < allLocations.getSize(); i++) {
        const Location& loc = allLocations.getAt(i);

        std::cout << "\n[" << i + 1 << "] Локация: " << loc.name.c_str() << std::endl;
        std::cout << "    " << loc.description.c_str() << std::endl;

        const StatVector& reqs = loc.requirements;
        if (reqs.size > 0) {
            std::cout << "    Требования: ";
            for (int k = 0; k < reqs.size; k++) {
                StatPair pair = reqs.getAt(k);
                std::cout << pair.key.c_str() << " >= " << pair.value << "  ";
            }
            std::cout << std::endl;
        }

        std::cout << "    Успех: " << loc.successText.c_str() << std::endl;
        std::cout << "    Провал: " << loc.failText.c_str() << std::endl;
    }

    std::cout << "\n================================" << std::endl;
}
Location LocationManager::getRandomLocation() {
    int count = allLocations.getSize();
    if (count <= 0) {
        return Location();
    }
    int randomIdx = rand() % count;
    Location baseLocation = allLocations.getAt(randomIdx);
    return baseLocation;
}