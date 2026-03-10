#include "Item.h"

Item::Item(const MyString& n, const MyString& desc,
    SlotType type, const StatVector& initialStats,
    bool found)
    : name(n), description(desc), slotType(type), stats(initialStats),
    isFoundItem(found) {
}

MyString Item::getName() const { return name; }
MyString Item::getDescription() const { return description; }
SlotType Item::getSlotType() const { return slotType; }
bool Item::isFound() const { return isFoundItem; }

int Item::getStat(const MyString& statName) const {
    return stats.getValue(statName);
}

const StatVector& Item::getStats() const {
    return stats;
}

Item& Item::operator=(const Item& other) {
    if (this != &other) {
        name=other.name;
        description=other.description;
        slotType=other.slotType;
        stats=other.stats;
        isFoundItem=other.isFoundItem;
    }
    return *this;
}

void Item::printInfo() const {
    std::cout << name << " (" << SlotTypeToMyString(slotType)
        << description << ") " << std::endl;
    if (!stats.empty()) {
        std::cout << "Характеристики: ";
        for (int i = 0; i < stats.size; i++) {
            StatPair pair = stats.getAt(i);
            std::cout << pair.key << ": " << pair.value;
            if (i < stats.size - 1) { std::cout << ", "; }
        }
        std::cout << "\n";
    }
}

MyString Item::SlotTypeToMyString(SlotType type) {
    switch (type) {
    case SlotType::HEAD:return "Голова";
    case SlotType::BODY:return "Тело";
    case SlotType::HANDS:return "Руки";
    case SlotType::FEET:return "Ноги";
    case SlotType::WEAPON:return "Оружие";
    case SlotType::SPECIAL:return "Особый";
    default: return "Нет";
    }
}
SlotType Item::MyStringToSlotType(MyString str) {
    if (str == "HEAD") return SlotType::HEAD;
    if (str == "BODY") return SlotType::BODY;
    if (str == "HANDS") return SlotType::HANDS;
    if (str == "FEET") return SlotType::FEET;
    if (str == "WEAPON") return SlotType::WEAPON;
    if (str == "SPECIAL") return SlotType::SPECIAL;
    return SlotType::NONE;
}