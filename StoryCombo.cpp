#include "StoryCombo.h"
bool StoryCombo::canExecute(const MyVector<MyString>& selected) const {
    if (selected.getSize() < requiredNames.getSize()) return false;
    for (int i = 0; i < requiredNames.getSize(); i++) {
        bool found = false;
        for (int j = 0; j < selected.getSize(); j++) {
            if (requiredNames.getAt(i) == selected.getAt(j)) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}
