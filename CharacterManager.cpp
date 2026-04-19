#define _CRT_SECURE_NO_WARNINGS
#include "CharacterManager.h"
#include <cstdio>
#include <cstring>

CharacterManager::CharacterManager(const MyString& filePath) : PlayersFilePath(filePath) {
}

bool CharacterManager::loadPlayersFromTXT(ItemManager& itemMgr) {
    for (int i = 0; i < 4; i++) allPlayers[i].clear();

    FILE* file = fopen(PlayersFilePath.c_str(), "r");
    if (!file) return false;

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char diffName[50];
        int charCount = 0;

        if (sscanf(line, "%s %d", diffName, &charCount) >= 2) {
            int diffIdx = 0;
            if (strcmp(diffName, "EASY") == 0) diffIdx = 0;
            else if (strcmp(diffName, "NORMAL") == 0) diffIdx = 1;
            else if (strcmp(diffName, "HARD") == 0) diffIdx = 2;
            else if (strcmp(diffName, "DEBUG_MOD") == 0) diffIdx = 3;

            for (int i = 0; i < charCount; i++) {
                do {
                    if (!fgets(line, sizeof(line), file)) break;
                    line[strcspn(line, "\r\n")] = 0;
                } while (strlen(line) == 0 || strcmp(line, "{") == 0 || strcmp(line, "}") == 0);
                MyString name = line;

                fgets(line, sizeof(line), file);
                line[strcspn(line, "\r\n")] = 0;
                MyString desc = line;

                fgets(line, sizeof(line), file);
                int statsCount = atoi(line);
                StatVector pStats(statsCount);

                for (int j = 0; j < statsCount; j++) {
                    if (fgets(line, sizeof(line), file)) {
                        char sName[50];
                        int sVal;
                        if (sscanf(line, "%49s %d", sName, &sVal) == 2) {
                            pStats.setAt(j, MyString(sName), sVal);
                        }
                    }
                }

                Player newPlayer(name, desc, pStats);

                if (fgets(line, sizeof(line), file)) {
                    int itemCount = atoi(line);

                    for (int j = 0; j < itemCount; j++) {
                        if (fgets(line, sizeof(line), file)) {
                            line[strcspn(line, "\r\n")] = 0;

                            if (strlen(line) == 0) {
                                j--;
                                continue;
                            }

                            Item* found = itemMgr.findItemByName(line);
                            if (found) {
                                newPlayer.equipItem(*found);
                            }
                            else {
                                printf("Предмет '%s' не найден в базе!\n", line);
                            }
                        }
                    }
                }
                allPlayers[diffIdx].push_back(newPlayer);

            }
        }
    }
    fclose(file);
    return true;
}
Player CharacterManager::getRandomPlayer(Difficulty diff) const {
    int idx = (int)diff;
    int count = allPlayers[idx].getSize();
    if (count <= 0) return Player("Ошибка", "Нет персонажей");
    return allPlayers[idx][rand() % count];
}
