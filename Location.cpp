#include "Location.h"

Location::Location(const MyString& n, const MyString& desc)
    : name(n), description(desc) {
}

bool Location::checkPath(const Player& player, int pathIdx) {
    if (pathIdx < 0 || pathIdx >= paths.getSize()) {
        return false;
    }
    const Path& p = paths.getAt(pathIdx);
    for (int i = 0; i < p.requirements.size; i++) {
        StatPair req = p.requirements.getAt(i);
        if (player.getStatValue(req.key) < req.value) {
            return false;
        }
    }
    return true;
}

MyString Location::getName() const {
    return name;
}
MyString Location::getDescription() const {
    return description;
}