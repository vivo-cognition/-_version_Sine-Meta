#include "Mission.h"

Mission::Mission(const MyString& n, const MyString& desc, const MyString& sdesc)
    : name(n), description(desc), secondDescription(sdesc) {
}

bool Mission::checkPath(const Player& player, int pathIdx) {
    if (pathIdx < 0 || pathIdx >= paths.getSize()) {
        return false;
    }
    const Path& p = paths[pathIdx];
    for (int i = 0; i < p.requirements.size; i++) {
        StatPair req = p.requirements.getAt(i);
        if (player.getStatValue(req.key) < req.value) {
            return false;
        }
    }
    return true;
}

MyString Mission::getName() const {
    return name;
}
MyString Mission::getDescription() const {
    return description;
}
MyVector <MyString> Mission::getAllNamePath() {
    MyVector <MyString> NamePaths;
    for (int i = 0; i < paths.getSize();i++) {
        NamePaths.push_back(paths[i].actionName);
    }
    return NamePaths;
}
MyString Mission::FailOrWin(Player player, int selected) {
    const Path& p = paths[selected];
    for (int i = 0; i < p.requirements.size; i++) {
        StatPair req = p.requirements.getAt(i);
        if (player.getStatValue(req.key) < req.value) {
            return p.failText;
        }
    }
    return p.successText;
}