#pragma once
#include "MyString.h"
#include "StatVector.h"

struct Path {
    MyString actionName;
    StatVector requirements;
    MyString successText;
    MyString failText;
    StatVector rewards;
};
