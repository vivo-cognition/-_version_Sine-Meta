#pragma once
#include "Player.h"
#include "LocationManager.h"
#include "ItemManager.h"
#include "CharacterManager.h"
#include "Mission.h"
#include "Shopman.h"
#include "ShopmanManager.h"
#include "StoryComboManager.h"
#include "StoryCombo.h"

struct Game {
    Player player;
    LocationManager locManager;
    ItemManager itemManager;
    CharacterManager charManager;
    StoryComboManager comboManager;

    Mission currentMission;
    Location currentLocation;
    Location currentEvent;
    ShopmanManager shopManager;

    bool isRunning;

    Game();

    void playIntro();
    void drawingMenu();
    void drawingShop();
    void drawingMissionAndLocation();
    void drawingInShop(int number);
    void inLocation();
    void findItem();
    void eventMeeting();
    void craftBlock();
    void final();

    void run();

    void startNewGame();
    void loadGame();
    void showStory();
    void choiceStartPlayer(int diff);
    void logPlayer();
};