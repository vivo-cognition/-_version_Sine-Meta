#define _CRT_SECURE_NO_WARNINGS
#include "StoryComboManager.h"

StoryComboManager::StoryComboManager(const MyString& comPath)
    : storyCombosFilePath(comPath) {
    loadCombosFromTxt();
}
bool StoryComboManager::loadCombosFromTxt() {
    allCombos.clear();
    FILE* file = fopen(storyCombosFilePath.c_str(), "r");
    if (!file) return false;

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char nameBuf[128];
        if (sscanf(line, "%s {", nameBuf) == 1) {
            StoryCombo combo;
            combo.comboName = MyString(nameBuf);
            fgets(line, sizeof(line), file);
            int itemsCount = atoi(line);
            for (int i = 0; i < itemsCount; i++) {
                fgets(line, sizeof(line), file);
                line[strcspn(line, "\r\n")] = 0;
                combo.requiredNames.push_back(MyString(line));
            }
            fgets(line, sizeof(line), file);
            combo.statusThreshold = atoi(line);
            fgets(line, sizeof(line), file);
            int rewCount = atoi(line);
            combo.rewards = StatVector(rewCount);
            for (int i = 0; i < rewCount; i++) {
                char sName[64]; int sVal;
                fgets(line, sizeof(line), file);
                sscanf(line, "%s %d", sName, &sVal);
                combo.rewards.setAt(i, MyString(sName), sVal);
            }
            fgets(line, sizeof(line), file);
            line[strcspn(line, "\r\n")] = 0;
            combo.successText = MyString(line);

            fgets(line, sizeof(line), file);
            line[strcspn(line, "\r\n")] = 0;
            combo.failText = MyString(line);

            fgets(line, sizeof(line), file);
            allCombos.push_back(combo);
        }
    }
    fclose(file);
    return true;
}
int StoryComboManager::getCombosCount() const {
    return allCombos.getSize();
}
const StoryCombo* StoryComboManager::checkAllCombos(const MyVector<MyString>& selectedItems) const {
    for (int i = 0; i < allCombos.getSize(); i++) {
        if (allCombos.getAt(i).canExecute(selectedItems)) {
            return &allCombos.getAt(i);
        }
    }
    return nullptr;
}