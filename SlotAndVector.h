#pragma once
#include <iostream>
#include "Enum.h"
#include "MyVector.h"
#include "Item.h"

struct SlotAndVector {
	SlotType slot;
	MyVector<Item> items;

	SlotAndVector();
	~SlotAndVector();

	Item& operator[](int index);
};
