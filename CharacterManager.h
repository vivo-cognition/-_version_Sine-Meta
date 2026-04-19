#pragma once
#include "MyVector.h"
#include "Player.h"
#include "ItemManager.h" 
struct CharacterManager {
    MyVector <Player> allPlayers[4];
    MyString PlayersFilePath;

    CharacterManager(const MyString& filePath = "StartPlayers.txt");

    bool loadPlayersFromTXT(ItemManager& itemMgr);

    Player getRandomPlayer(Difficulty diff) const;

    bool isLoaded() const;
};
