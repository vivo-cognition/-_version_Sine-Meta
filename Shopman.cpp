#include "Shopman.h"

Shopman::Shopman(ShopType type,
    const MyVector<MyString>& d,
    const MyString& c,
    const StatVector& initialStats,
    const MyVector<MyString>& s)
    : Name(type),
    Dialogs(d),
    CloseShop(c),
    Stat(initialStats),
    SpecialDialogs(s)
{
}



MyString Shopman::ShopTypeToMyString(ShopType type) {
    switch (type) {
    case ShopType::OLD_MAN: return "Старик";
    case ShopType::MAIDEN:return "Девица";
    case ShopType::WITCH:return "Ведьма";
    case ShopType::FOREIGNER:return "Иностранец";
    default: return "Нет";
    }
}
 ShopType Shopman::MyStringToShopType(MyString str) {
    if (str == "Старик") return ShopType::OLD_MAN;
    if (str == "Девица") return ShopType::MAIDEN;
    if (str == "Ведьма") return ShopType::WITCH;
    if (str == "Иностранец") return ShopType::FOREIGNER;
    return ShopType::OLD_MAN;
}