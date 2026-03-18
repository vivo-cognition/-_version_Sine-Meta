#include "Location.h"

Location::Location(const MyString& n, const MyString& desc, const StatVector& req, const MyString& success, const MyString& fail)
    : name(n), description(desc), requirements(req), successText(success), failText(fail) {}

bool Location::checkVictory(const Player& player) {
    for (int i = 0; i < requirements.size; i++) {
        StatPair req = requirements.getAt(i);
        int playerStat = player.getStatValue(req.key);
        if (playerStat < req.value) {
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