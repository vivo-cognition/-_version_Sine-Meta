#pragma once
#include "Player.h"
#include "LocationManager.h"
#include "ItemManager.h"

struct Game {
	Player player;
	LocationManager locManager;
	ItemManager itemManager;
	bool isRunning;
	int currentLocIdx;

	Game();
	void init();
	void run();
	void processInput();
	void handleLocation();
//  void update();
//  void render();
};