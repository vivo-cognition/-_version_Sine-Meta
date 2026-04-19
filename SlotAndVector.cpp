#include "SlotAndVector.h"

SlotAndVector::SlotAndVector() : slot(SlotType::NONE) {}

SlotAndVector::~SlotAndVector() {}
Item& SlotAndVector::operator[](int index) {
    return items[index];
}
