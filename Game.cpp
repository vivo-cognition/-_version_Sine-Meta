#include "Game.h"
#include <iostream>
#include "MyString.h"
#include <thread>
#include <chrono>
#include <windows.h> 
Game::Game() {
    isRunning = true;
    if (!itemManager.loadItemsFromTXT()) {
        std::cout << "Ошибка загрузки предметов!" << std::endl;
    }
    if (!charManager.loadPlayersFromTXT(itemManager)) {
        std::cout << "Ошибка загрузки персонажей!" << std::endl;
    }
    if (!locManager.loadEventsFromTxt()) {
        std::cout << "Ошибка загрузки событий"<<std::endl;
    }
    if (!locManager.loadLocationsFromTxt()) {
        std::cout << "Ошибка загрузки локаций" << std::endl;
    } 
    if (!locManager.loadMissionsFromTxt()) {
        std::cout << "Ошибка загрузки финала" << std::endl;
    }
    if (!shopManager.loadShopmansFromTxt()) {
        std::cout << "Ошибка загрузки артов торговцев" << std::endl;
    }
    if (!shopManager.loadDialogsFromTxt()) {
        std::cout << "Ошибка загрузки диалогов" << std::endl;
    }
    if (!comboManager.loadCombosFromTxt()) {
        std::cout << "Ошибка загрузки комбо" << std::endl;
    }
    run();
}
void Game::run() {
    playIntro();
    drawingMenu();
}
void Game::startNewGame() {
    logPlayer();
    drawingMissionAndLocation();
    drawingShop();
    inLocation();
    findItem();
    eventMeeting();
    craftBlock();
    final();
}