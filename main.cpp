#include <iostream>
#include "ItemManager.h"
#include <Windows.h>
int main() {
    SetConsoleOutputCP(1251);
    ItemManager manager("Items.txt");

    if (manager.loadItemsFromTXT()) {
        std::cout << "--- УСПЕХ: Файл загружен успешно! ---" << std::endl;
    }
    else {
        std::cerr << "--- ОШИБКА: Не удалось загрузить файл! ---" << std::endl;
        return 1; // Завершаем программу с ошибкой
    }
  /*  int total = manager.getTotalItemCount();
    std::cout << "Всего предметов в базе: " << total << std::endl;

    // 4. Печатаем все предметы (если ты реализовала printAllItems)
    // Это лучший способ увидеть, правильно ли считались имена, описания и статы
    manager.printAllItems();

    // 5. Проверка конкретного слота (например, FEET - индекс 1)
    const ItemVector& boots = manager.getItemBySlot(FEET);
    std::cout << "Предметов в слоте FEET: " << boots.getSize() << std::endl;

    if (boots.getSize() > 0) {
        std::cout << "Первый предмет в сапогах: " << boots.getAt(0).getName().c_str() << std::endl;
    }*/

    std::cout << "\nНажмите Enter, чтобы выйти...";
    std::cin.get();

    return 0;
}
