#pragma once
#include "Enum.h"
#include "MyString.h"
#include "StatVector.h"

struct Item {
	MyString name;
	MyString description;
	SlotType slotType;
	StatVector stats;
	bool isFoundItem;

	Item(const MyString& n = "Ничего",
		const MyString& desc = "Пустой слот",
		SlotType type = SlotType::NONE,
		const StatVector& initialStats = StatVector(0),
		bool found = false);

	MyString getName() const;
	MyString getDescription() const;
	SlotType getSlotType() const;
	bool isFound() const;

	int getStat(const MyString& statName) const;
	const StatVector& getStats() const;

	Item& operator=(const Item& other);

	void printInfo() const;
	static MyString SlotTypeToMyString(SlotType type);
	static SlotType MyStringToSlotType(MyString str);
};