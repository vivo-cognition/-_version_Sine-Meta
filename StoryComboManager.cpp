#define _CRT_SECURE_NO_WARNINGS
#include "StoryComboManager.h"

StoryComboManager::StoryComboManager(const MyString& comPath)
    : storyCombosFilePath(comPath) {
    std::cout << "DEBUG PATH: " << storyCombosFilePath.c_str() << std::endl;
    loadCombosFromTxt();
}
void trim(char* s) {
    s[strcspn(s, "\r\n")] = 0;
    int len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1])) {
        s[--len] = 0;
    }
}

bool StoryComboManager::loadCombosFromTxt() {
    allCombos.clear();
    FILE* file = fopen(storyCombosFilePath.c_str(), "r");
    if (!file) {
        std::cout << "Error: Could not open " << storyCombosFilePath << std::endl;
        return false;
    }
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char nameBuf[128];
        if (sscanf(line, "%127s", nameBuf) == 1) {
            if (strcmp(nameBuf, "}") == 0 || strcmp(nameBuf, "{") == 0) continue;
            StoryCombo combo;
            combo.comboName = MyString(nameBuf);
            do { if (!fgets(line, sizeof(line), file)) break; trim(line); } while (strlen(line) == 0);
            int itemsCount = atoi(line);
            for (int i = 0; i < itemsCount; i++) {
                do { if (!fgets(line, sizeof(line), file)) break; trim(line); } while (strlen(line) == 0);
                if (strlen(line) > 0) {
                    combo.requiredNames.push_back(MyString(line));
                }
            }
            do { if (!fgets(line, sizeof(line), file)) break; trim(line); } while (strlen(line) == 0);
            combo.statusThreshold = atoi(line);
            do { if (!fgets(line, sizeof(line), file)) break; trim(line); } while (strlen(line) == 0);
            int rewCount = atoi(line);
            combo.rewards = StatVector(rewCount);
            for (int i = 0; i < rewCount; i++) {
                do { if (!fgets(line, sizeof(line), file)) break; trim(line); } while (strlen(line) == 0);
                char sName[64];
                int sVal;
                if (sscanf(line, "%s %d", sName, &sVal) == 2) {
                    combo.rewards.setAt(i, MyString(sName), sVal);
                }
            }
            do { if (!fgets(line, sizeof(line), file)) break; trim(line); } while (strlen(line) == 0);
            combo.successText = MyString(line);
            do { if (!fgets(line, sizeof(line), file)) break; trim(line); } while (strlen(line) == 0);
            combo.failText = MyString(line);
            if (combo.requiredNames.getSize() > 0) {
                allCombos.push_back(combo);
                std::cout << "Успешно загружено комбо: " << combo.comboName.c_str() << std::endl;
            }
        }
    }
    fclose(file);
    return true;
}
int StoryComboManager::getCombosCount() const {
    return allCombos.getSize();
}
const StoryCombo* StoryComboManager::checkAllCombos(const MyVector<Item>& selectedItems) const {
    MyVector <MyString> sI;
    for (int j = 0;j < selectedItems.getSize();j++) {
        sI.push_back(selectedItems[j].getName());
    }
    for (int i = 0; i < allCombos.getSize(); i++) {
        if (allCombos[i].canExecute(sI)) {
            return &allCombos[i];
        }
    }
    return nullptr;
}