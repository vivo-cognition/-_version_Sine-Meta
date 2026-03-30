#pragma once
#include "MyVector.h"
#include "MyString.h"
#include "StatVector.h"

struct StoryCombo {
    MyString comboName;
    MyVector<MyString> requiredNames;
    int statusThreshold;
    StatVector rewards;
    MyString successText;
    MyString failText;

    bool canExecute(const MyVector<MyString>& selected) const;
};
