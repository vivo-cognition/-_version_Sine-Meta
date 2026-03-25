#include "Game.h"


void Game::handleLocation() {
    Location& loc = locManager.allLocations.getAt(currentLocIdx);

    std::cout << "\n=== " << loc.getName().c_str() << " ===" << std::endl;
    std::cout << loc.getDescription().c_str() << std::endl;

    for (int i = 0; i < loc.paths.getSize(); i++) {
        std::cout << i + 1 << ". " << loc.paths.getAt(i).actionName.c_str() << std::endl;
        std::cout << i + 1 << ". " << loc.paths.getAt(i).actionName.c_str() << std::endl;
    }
    int choice; int count = loc.paths.getSize();
    while (count > 0) {
        std::cout << "\nВаш выбор: ";
        std::cin >> choice;
        int idx = choice - 1;
        if (idx >= 0 && idx < loc.paths.getSize()) {
            Path& selectedPath = loc.paths.getAt(idx);

            if (loc.checkPath(player, idx)) {
                std::cout << "\n[УСПЕХ]: " << selectedPath.successText.c_str() << std::endl;
                player.applyStatChange(selectedPath.rewards);
                currentLocIdx++;
                break;
            }
            else {
                std::cout << "\n[ПРОВАЛ]: " << selectedPath.failText.c_str() << std::endl;
                std::cout << "\nПопробуйте снова" << std::endl;
            }
        }
    }
    std::cout << "\nУ вас не получилось приблизиться к цели это конец" << std::endl;
    
}

void Game::run() {
    while (isRunning && currentLocIdx < locManager.allLocations.getSize()) {
        handleLocation();
        if (currentLocIdx >= locManager.allLocations.getSize()) {
            std::cout << "Поздравляем! Вы прошли все испытания!" << std::endl;
            isRunning = false;
        }
    }
}