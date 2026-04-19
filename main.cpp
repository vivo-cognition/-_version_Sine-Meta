#include <iostream>
#include <Windows.h>
#include <ctime> 
#include "Game.h"
#include <fcntl.h> 
#include <io.h> 
#include "StoryComboManager.h"
int main() {
    srand(static_cast<unsigned int>(time(0)));
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    Game newGame;
    return 0;
}
