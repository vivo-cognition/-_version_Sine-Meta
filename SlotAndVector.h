#pragma once
#include <iostream>
#include "Enum.h"
#include "ItemVector.h"

struct SlotAndVector {
	SlotType slot;
	ItemVector items;

	SlotAndVector();
	~SlotAndVector();
};
