#include "Player.h"
#include <iostream>

Player::Player(const MyString& n, const MyString& d) : name(n), desc(d), totalStats(0) {}
Player::Player(const MyString& n, const MyString& d, const StatVector& s)
    : name(n), desc(d), totalStats(s) {}
void Player::equipItem(const Item& item) {
    inventory.push_back(item);
    const StatVector& itemStats = item.getStats();
    for (int i = 0; i < itemStats.size; i++) {
        StatPair pair = itemStats.getAt(i);
        this->totalStats.addOrUpdate(pair.key, pair.value);
    }
}
void Player::unEquipItem(const Item& item) {
    MyVector <Item> temp;
    for (int i = 0; i < inventory.getSize();i++) {
        if (inventory[i].getName() == item.getName()) {
            const StatVector& itemStats = item.getStats();
            for (int j = 0; j < itemStats.size; j++) {
                StatPair pair = itemStats.getAt(j);
                this->totalStats.addOrUpdate(pair.key, pair.value*(-1));
            }
            continue;
        }
        temp.push_back(inventory[i]);
    }
    inventory = temp;
}
Item Player::findItemInSlot(SlotType targetSlotType) {
    for (int i = 0; i < inventory.getSize(); i++) {
        if (inventory[i].getSlotType() == targetSlotType) {
            return inventory[i];
        }
    }
    return Item();
}

int Player::getStatValue(const MyString& statName) const {
    return totalStats.getValue(statName);
}

void Player::printStatus() const {
    std::cout << "\n============================";
    std::cout << "\nÈÃÐÎÊ: " << name.c_str();
    std::cout << "\nÈÍÂÅÍÒÀÐÜ: " << inventory.getSize() << " ïðåäìåòîâ.";
    for (int i = 0;i < inventory.getSize();i++) {
        Item temp = inventory[i];
        std::cout << "\n   Ïðåäìåò ¹" << i+1 << " " << temp.getName() << " (" << temp.getDescription() << " )";
    }
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
bool Player::canPassRequirements(const StatVector& requirements) const {
    for (int i = 0; i < requirements.size; ++i) {
        MyString statName = requirements.getAt(i).key;
        int neededValue = requirements.getAt(i).value;
        if (this->getStatValue(statName) < neededValue) {
            return false;
        }
    }
    return true;
}
MyVector <MyString> Player::getItemsBySlot(SlotType targetSlotType) {
    MyVector <MyString> playerItems;
    for (int i = 0; i < inventory.getSize(); i++) {
        if (inventory[i].getSlotType() == targetSlotType) {
            playerItems.push_back(inventory[i].getName());
        }
    }
    return playerItems;
}