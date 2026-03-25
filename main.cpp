#include <iostream>
#include <Windows.h>
#include "ItemManager.h"
#include "Player.h"
#include <ctime> 
#include "LocationManager.h"

int main() {
    srand(static_cast<unsigned int>(time(0)));
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    ItemManager manager("Items.txt");
    if (!manager.isLoaded()) {
        std::cout << "Критическая ошибка: файл Items.txt не найден!" << std::endl;
        system("pause");
        return 1;
    }
    Player igrok("Странник");
    std::cout << "--- Добро пожаловать в игру! ---" << std::endl;
    Item randomItem = manager.generateRandomFoundItem();
    std::cout << "Вы нашли: " << randomItem.getName().c_str()<< std::endl<< randomItem.getDescription() <<std::endl;
    igrok.equipItem(randomItem);
    igrok.printStatus();

    randomItem = manager.generateRandomFoundItem();
    std::cout << "Вы нашли: " << randomItem.getName() << std::endl << randomItem.getDescription() << std::endl;
    igrok.equipItem(randomItem);
    igrok.printStatus();

    LocationManager manager1("Locations.txt");
    manager1.printAllLocations();
    Location randomLocation = manager1.getRandomLocation();
    std::cout << "\nРандомная локации " << randomLocation.getName() << std::endl << randomLocation.getDescription() << std::endl;

    LocationManager manager2("Evtnts.txt");
    Location randomEvent = manager2.getRandomEventByType("CASTLE");
    std::cout << "\nРандомное событие " << randomEvent.getName() << std::endl << randomEvent.getDescription() << std::endl;
    
    std::cout << "Нажмите Enter для завершения...";
    std::cin.get();
    return 0;
}
