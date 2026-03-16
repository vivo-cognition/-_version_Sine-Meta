#include "Location.h"

Location::Location(const MyString& n, const MyString& desc, const StatVector& req, const MyString& success, const MyString& fail)
    : name(n), description(desc), requirements(req), successText(success), failText(fail) {}

bool Location::checkVictory(const Player& player, const Location& loc) {
    for (int i = 0; i < loc.requirements.size; i++) {
        StatPair req = loc.requirements.getAt(i);
        int playerStat = player.getStatValue(req.key);
        if (playerStat < req.value) {
            return false;
        }
    }
    return true;
}