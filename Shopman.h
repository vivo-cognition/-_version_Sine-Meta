#pragma once
#include "MyString.h"
#include "MyVector.h"
#include "StatVector.h"
#include "Enum.h"

struct Shopman {
	ShopType Name;
    MyVector <MyString> Dialogs;
    MyString CloseShop;
	StatVector Stat;
    MyVector <MyString> SpecialDialogs;

    Shopman(ShopType type = ShopType::OLD_MAN,
        const MyVector<MyString>& d = MyVector<MyString>(),
        const MyString& c = MyString(""),
        const StatVector& initialStats = StatVector(0),
        const MyVector<MyString>& s = MyVector<MyString>());
    static MyString ShopTypeToMyString(ShopType type);
    static ShopType MyStringToShopType(MyString str);
};

