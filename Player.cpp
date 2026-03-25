#include "Player.h"
#include <iostream>

Player::Player(const MyString& n) : name(n), totalStats(0) {}

void Player::equipItem(const Item& item) {
    inventory.push_back(item);
    const StatVector& itemStats = item.getStats();
    for (int i = 0; i < itemStats.size; i++) {
        StatPair pair = itemStats.getAt(i);
        this->totalStats.addOrUpdate(pair.key, pair.value);
    }
}

int Player::getStatValue(const MyString& statName) const {
    return totalStats.getValue(statName);
}

void Player::printStatus() const {
    std::cout << "\n============================";
    std::cout << "\nÈÃÐÎÊ: " << name.c_str();
    std::cout << "\nÈÍÂÅÍÒÀÐÜ: " << inventory.getSize() << " ïðåäìåòîâ.";
    std::cout << "\nÒÅÊÓÙÈÅ ÕÀÐÀÊÒÅÐÈÑÒÈÊÈ:";

    if (totalStats.size == 0) {
        std::cout << "\n  (ñòàòû îòñóòñòâóþò)";
    }
    else {
        for (int i = 0; i < totalStats.size; i++) {
            StatPair stat = totalStats.getAt(i);
            std::cout << "\n  > " << stat.key.c_str() << ": " << stat.value;
        }
    }
    std::cout << "\n============================\n";
}
void Player::applyStatChange(const StatVector& rewards) {
    for (int i = 0; i < rewards.size; i++) {
        StatPair reward = rewards.getAt(i);
        totalStats.addOrUpdate(reward.key, reward.value);
    }
}
