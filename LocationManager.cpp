#define _CRT_SECURE_NO_WARNINGS
#include "LocationManager.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

LocationManager::LocationManager(const MyString& locPath, const MyString& eventPath)
    : locationsFilePath(locPath), eventsFilePath(eventPath) {
    loadLocationsFromTxt();
    loadEventsFromTxt();
}

bool LocationManager::loadLocationsFromTxt() {
    allLocations.clear();
    FILE* file = fopen(locationsFilePath.c_str(), "r");
    if (!file) return false;

    char line[1024];
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
                int pathsCount = atoi(line);
                for (int p = 0; p < pathsCount; p++) {
                    Path newPath;
                    fgets(line, sizeof(line), file);
                    line[strcspn(line, "\r\n")] = 0;
                    newPath.actionName = MyString(line);

                    fgets(line, sizeof(line), file);
                    int reqCount = atoi(line);
                    newPath.requirements = StatVector(reqCount);
                    for (int i = 0; i < reqCount; i++) {
                        char sName[64]; int sVal;
                        fgets(line, sizeof(line), file);
                        sscanf(line, "%s %d", sName, &sVal);
                        newPath.requirements.setAt(i, MyString(sName), sVal);
                    }
                    fgets(line, sizeof(line), file);
                    int rewardsCount = atoi(line);
                    newPath.rewards = StatVector(rewardsCount);
                    for (int i = 0; i < rewardsCount; i++) {
                        char rName[64]; int rVal;
                        fgets(line, sizeof(line), file);
                        if (sscanf(line, "%s %d", rName, &rVal) == 2) {
                            newPath.rewards.setAt(i, MyString(rName), rVal);
                        }
                    }
                    fgets(line, sizeof(line), file);
                    line[strcspn(line, "\r\n")] = 0;
                    newPath.successText = MyString(line);

                    fgets(line, sizeof(line), file);
                    line[strcspn(line, "\r\n")] = 0;
                    newPath.failText = MyString(line);

                    newLoc.paths.push_back(newPath);
                }
            }
            fgets(line, sizeof(line), file);
            allLocations.push_back(newLoc);
        }
    }
    fclose(file);
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

        for (int j = 0; j < loc.paths.getSize(); j++) {
            const Path& path = loc.paths.getAt(j);
            std::cout << "\n    Путь №" << j + 1 << ": " << path.actionName.c_str();
            if (path.rewards.size > 0) {
                std::cout << "\n    Награда: ";
                for (int k = 0; k < path.rewards.size; k++) {
                    StatPair pair = path.rewards.getAt(k);
                    std::cout << "+" << pair.value << " " << pair.key.c_str() << "  ";
                }
            }
            if (path.requirements.size > 0) {
                std::cout << "\n    Требования: ";
                for (int k = 0; k < path.requirements.size; k++) {
                    StatPair pair = path.requirements.getAt(k);
                    std::cout << pair.key.c_str() << " >= " << pair.value << " ";
                }
            }
            else {
                std::cout << "\n    Требования: отсутствуют";
            }

            std::cout << "\n    Результат успеха: " << path.successText.c_str();
            std::cout << "\n    Результат провала: " << path.failText.c_str() << std::endl;
        }
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
bool LocationManager::loadEventsFromTxt() {
    eventPool.clear();
    FILE* file = fopen(eventsFilePath.c_str(), "r");
    if (!file) return false;
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char tag[64];
        if (sscanf(line, "%s {", tag) == 1) {
            Location newEvent;
            newEvent.name = MyString(tag);
            if (fgets(line, sizeof(line), file)) {
                line[strcspn(line, "\r\n")] = 0;
                newEvent.description = MyString(line);
            }
            if (fgets(line, sizeof(line), file)) {
                int pathsCount = atoi(line);
                for (int p = 0; p < pathsCount; p++) {
                    Path newPath;
                    fgets(line, sizeof(line), file);
                    line[strcspn(line, "\r\n")] = 0;
                    newPath.actionName = MyString(line);
                    fgets(line, sizeof(line), file);
                    int reqCount = atoi(line);
                    newPath.requirements = StatVector(reqCount);
                    for (int i = 0; i < reqCount; i++) {
                        char sName[64]; int sVal;
                        fgets(line, sizeof(line), file);
                        sscanf(line, "%s %d", sName, &sVal);
                        newPath.requirements.setAt(i, MyString(sName), sVal);
                    }
                    fgets(line, sizeof(line), file);
                    int rewardsCount = atoi(line);
                    newPath.rewards = StatVector(rewardsCount);
                    for (int i = 0; i < rewardsCount; i++) {
                        char rName[64]; int rVal;
                        fgets(line, sizeof(line), file);
                        if (sscanf(line, "%s %d", rName, &rVal) == 2) {
                            newPath.rewards.setAt(i, MyString(rName), rVal);
                        }
                    }
                    fgets(line, sizeof(line), file);
                    line[strcspn(line, "\r\n")] = 0;
                    newPath.successText = MyString(line);
                    fgets(line, sizeof(line), file);
                    line[strcspn(line, "\r\n")] = 0;
                    newPath.failText = MyString(line);
                    newEvent.paths.push_back(newPath);
                }
            }
            fgets(line, sizeof(line), file);
            eventPool.push_back(newEvent);
        }
    }
    fclose(file);
    return true;
}

Location LocationManager::getRandomEventByType(const MyString& type) {
    MyVector<Location> filteredEvents;
    for (int i = 0; i < eventPool.getSize(); i++) {
        const Location& ev = eventPool.getAt(i);
        if (ev.name == type || ev.name == MyString("GLOBAL")) {
            filteredEvents.push_back(ev);
        }
    }
    if (filteredEvents.getSize() == 0) return Location();
    int randomIdx = rand() % filteredEvents.getSize();
    return filteredEvents.getAt(randomIdx);
}
