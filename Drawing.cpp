#include "Game.h"
#include <iostream>
#include "MyString.h"
#include "MyVector.h"
#include <thread>
#include <chrono>
#include <windows.h> 
#include <conio.h>
#include <fcntl.h> 
#include <io.h> 
void setColor(int text, int background) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
void setCursor(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void output(const MyString& Text) {
    bool skip = false;
    for (int i = 0; i < Text.size(); i++) {
        std::cout << Text[i] << std::flush;
        if (!skip) {
            if (_kbhit()) {
                _getch();
                skip = true;
            }
            Sleep(60);
        }
    }
}
void clearLine(int x, int y, int width) {
    setCursor(x, y);
    for (int i = 0; i < width; ++i) std::cout << " ";
}

//интро
void drawIntroArt(int startY) {
    setColor(5, 15);

    const char* l0 = R"(          .--------.          )";
    const char* l1 = R"(        /          \        )";
    const char* l2 = R"(       /   ______   \       )";
    const char* l3 = R"(      |   /      \   |      )";
    const char* l4 = R"(      |  |  (  )  |  |      )";
    const char* l5 = R"(      |   \______/   |      )";
    const char* l6 = R"(       \    ____    /       )";
    const char* l7 = R"(        \  /    \  /        )";
    const char* l8 = R"(         `|______|`         )";
    const char* l9 = R"(      _.-'        '-._      )";
    const char* l10 = R"(    -'                '-    )";

    const char* layers[] = { l0, l1, l2, l3, l4, l5, l6, l7, l8, l9, l10 };

    for (int i = 0; i < 11; i++) {
        setCursor(25, startY + i);
        std::cout << layers[i];
    }
}
void Game::playIntro() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    system("cls");
    const char* s[] = { " ____ ", "/ ___|", "\\___ \\", " ___) |", "|____/ " };
    const char* n[] = { " _   _ ", "| \\ | |", "|  \\| |", "| |\\  |", "|_| \\_|" };
    const char* e[] = { " _____ ", "| ____|", "|  _|  ", "| |___ ", "|_____|" };
    const char* m[] = { " __  __ ", "|  \\/  |", "| |\\/| |", "| |  | |", "|_|  |_|" };
    const char* t[] = { " _____ ", "|_   _|", "  | |  ", "  | |  ", "  |_|  " };
    const char* a[] = { "    _    ", "   / \\   ", "  / _ \\  ", " / ___ \\ ", "/_/   \\_\\" };
    const char* sword[] = {
        "  /\\",
        "  ||  ",
        "--||--",
        "  ||  ",
        "  ||  ",
        "  \\/  "
    };
    short cX = 30;
    short cY = 5;
    system("color 07");
    setColor(12, 0);
    for (int i = 0; i < 6; i++) {
        setCursor(cX - 3, cY + i);
        std::cout << sword[i];
        Sleep(90);
    }
    SetConsoleTextAttribute(hConsole, 7);
    for (int i = 0; i < 5; i++) {
        setCursor(cX - 12, cY + i);
        std::cout << s[i];
        setCursor(cX + 4, cY + i);
        std::cout << n[i] << e[i];
        setCursor(cX + 22, cY + i);
        std::cout << m[i] << e[i] << t[i] << a[i];
        Sleep(150);
    }
    Sleep(1500);
    system("color F0");
    system("cls");

    for (int i = 0; i < 6; i++) {
        setCursor(cX - 3, cY + i);
        setColor(4, 15);
        std::cout << sword[i];
        if (i < 5) {
            setColor(0, 15);
            setCursor(cX - 12, cY + i);
            std::cout << s[i];
            setCursor(cX + 4, cY + i);
            std::cout << n[i] << e[i];
            setCursor(cX + 22, cY + i);
            std::cout << m[i] << e[i] << t[i] << a[i];
        }
    }
    MyString text1 = "Текстовое RPG Sine Meta";
    MyString text2 = "Без страха. Без цели.";

    setColor(0, 15);
    setCursor(cX - 5, cY + 9);
    for (int i = 0; i < text1.size(); i++) {
        std::cout << text1[i] << std::flush;
        Sleep(40);
    }
    setCursor(cX - 4, cY + 11);
    setColor(8,15);
    for (int i = 0; i < text2.size(); i++) {
        std::cout << text2[i] << std::flush;
        Sleep(60);
    }
    Sleep(200);
    setCursor(cX - 6, cY + 14);
    setColor(4, 15);
    std::cout << "[ Нажмите любую клавишу ]";
    system("pause > nul");
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    setColor(4, 15);
}

//вызов меню новая игра | сохранение | история | выход
void Game::drawingMenu() {
    MyVector<MyString> menuItems;
    menuItems.push_back("Новая игра");
    menuItems.push_back("Слот сохранения");
    menuItems.push_back("Предыстория");
    menuItems.push_back("Выход");
    int selected = 0;
    bool inMenu = true;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
    system("cls");

    setCursor(10, 25);  std::cout << "      /\\ ";
    setCursor(10, 26);  std::cout << "     /  \\ ";
    setCursor(10, 27);  std::cout << "    /____\\ ";
    
    setColor(2, 15);
    setCursor(55, 20); std::cout << "     [  ]   ";
    setCursor(55, 21); std::cout << "    /    \\  ";
    setCursor(55, 22); std::cout << "   |  ~~  | ";
    setCursor(55, 23); std::cout << "    \\____/  ";

    setColor(0, 15); 
    setCursor(5, 3); std::cout << "      /\\  ";
    setCursor(5, 4); std::cout << "     |  | ";
    setCursor(5, 5); std::cout << "     |  | ";
    setCursor(5, 6); std::cout << "    --  --";
    setCursor(5, 7); std::cout << "      ||  ";
     
    while (inMenu) {
        setCursor(40, 5);
        setColor(12, 15);
        std::cout << "=== SINE META ===\n"; 
        setColor(0, 15);
        setCursor(45, 7);
        std::cout << " МЕНЮ ";
        setColor(0, 50);
        for (int i = 0; i < menuItems.getSize(); ++i) {
            setCursor(40, 7 +2+ i); 
            if (i == selected) {
                setColor(0, 12);
                std::cout << " " <<menuItems[i] << " ";
                setColor(0, 15);
            }
            else {
                setColor(0, 15);
                std::cout <<" " << menuItems[i]<<" ";
            }
        }
     
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) selected = (selected - 1 + menuItems.getSize()) % menuItems.getSize();
            else if (key == 80) selected = (selected + 1) % menuItems.getSize();
        }
        else if (key == 13) {
            info.bVisible = TRUE;
            SetConsoleCursorInfo(consoleHandle, &info);

            system("cls");
            switch (selected) {
            case 0: startNewGame(); inMenu = false; break;
            case 1: loadGame(); break;
            case 2: showStory(); break; 
            case 3: isRunning = false; inMenu = false; break;
            }
        }
    }
}

//вызов меню сложности и выбор начального персонажа + отрисовка арта + отрисовка карты игрока
void Game::logPlayer() {
    system("cls");
    setCursor(30, 40);
    drawIntroArt(10); setCursor(0, 0);
    int cX = 30;
    int cY = 20;
    setCursor(0, 0);
    MyString text = "Добро пожаловать в игру! Но перед тем как начать вам необходима оболочка для взаимодействия с нашим миром. Вам предоставиться на время прохождения игры тело одного из персонажей этого мира. Не волнуйтесь сейчас он находится в глубоком сне и ничего не вспомнит из того, что произойдёт. Вы сможете использовать вещи или статы, которые есть у него.\n";
    setColor(0, 15);
    output(text);
    MyString text1 = "Сложность прохождения определяется в начале игры и зависит от выбора начального персонажа.";
    setColor(8, 15);
    output(text1); 
    _getch();
    system("cls");
    setCursor(35, 7);
    setColor(12, 15); 
    std::cout<< "===Выберите сложность игры===";
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
    MyVector<MyString> levelItems;
    levelItems.push_back("Легко");
    levelItems.push_back("Нормально");
    levelItems.push_back("Сложно");
    levelItems.push_back("Режим истории");
    int selected = 0;
    bool inChoice = true;
    while (inChoice) {
        setColor(0, 50);
        for (int i = 0; i < levelItems.getSize(); ++i) {
            setCursor(40, 7 + 2 + i);
            if (i == selected) {
                setColor(0, 12);
                std::cout << " " << levelItems[i] << " ";
                setColor(0, 15);
            }
            else {
                setColor(0, 15);
                std::cout << " " << levelItems[i] << " ";
            }
        }
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) selected = (selected - 1 + levelItems.getSize()) % levelItems.getSize();
            else if (key == 80) selected = (selected + 1) % levelItems.getSize();
        }
        else if (key == 13) {
            info.bVisible = TRUE;
            SetConsoleCursorInfo(consoleHandle, &info);
            system("cls");
            switch (selected) {
            case 0: choiceStartPlayer(1); inChoice = false; break;
            case 1: choiceStartPlayer(2); inChoice = false; break;
            case 2: choiceStartPlayer(3); inChoice = false; break;
            case 3: choiceStartPlayer(4); inChoice = false; break;
            }
        }
    }
}
void printWrapped(MyString text, int startX, int& currentY, int maxWidth, int speed) {
    int printedInLine = 0;
    setCursor(startX, currentY++);
    for (int i = 0; i < text.size(); i++) {
        if (printedInLine >= maxWidth) {
            setCursor(startX, currentY++);
            printedInLine = 0;
            Sleep(speed);
        }
        std::cout << text[i];
        printedInLine++;
        Sleep(10);
    }
}
void drawPlayerCard(const Player& player, int startX, int startY) {
    int currentY = startY;
    int limitWidth = 45;
    setColor(12, 15);
    setCursor(startX, currentY++);
    output("============================================");
    setCursor(startX, currentY++);
    output("ИГРОК: "); output(player.name);
    for (int i = 0; i < player.inventory.getSize(); i++) {
        Item temp = player.inventory[i];
        MyString itemLine = " Предмет #";
        char buf[10];
        _itoa_s(i + 1, buf, 10);
        itemLine += " ";
        itemLine += temp.getName();
        itemLine += " (";
        itemLine += temp.getDescription();
        itemLine += ")";
        printWrapped(itemLine, startX, currentY, limitWidth,10);
    }
    printWrapped("ТЕКУЩИЕ ХАРАКТЕРИСТИКИ:",startX,currentY,limitWidth,10);
    for (int i = 0; i < player.totalStats.size; i++) {
        StatPair stat = player.totalStats.getAt(i);
        MyString statLine = "  > ";
        statLine += stat.key;
        statLine += ": ";
        char valBuf[15];
        _itoa_s(stat.value, valBuf, 10);
        statLine += valBuf;
        printWrapped(statLine, startX, currentY, limitWidth,10);
    }
    setCursor(startX, currentY++);
    output("============================================");
}
void drawMedievalTown(int startY) {
    setColor(8, 15); 
    const char* layer0 = R"(                        ___    #                                                          )";
    const char* layer1 = R"(   ^         ^   ______|[] \    #_   _           /\         ^         ___          /\     )";
    const char* layer2 = R"(  / \       / \|=======|[] [\     ||/ \_        /  \      _/ \_      /|||\________/  \    )";
    const char* layer3 = R"( /***\ __  /   \{} {}  |[] [] |   |/    \   @@ /... \    /*****\ /\ /|||||\      /    \   )";
    const char* layer4 = R"(|  []  |  ||  [#] |} {}|[] [] |  ||  []  |@@@@|  []  |   |  []  |++||  [#] |____|  []  | )";
    const char* layer5 = R"(|  __  |  ||  __  |____|  __  |  ||  __  |_||_|[]__[]|   |  __  |++||  __  |~~~~|  ==  | )";
    const char* layer6 = R"(|_|--|_|__||_||||_|_||_|_|++|_|@_||_|  |_|_||_|_|  |_|---|_|--|_|__||_||||_|++++|_|  |_|@)";

    setCursor(0, startY);     std::cout << layer0;
    setCursor(0, startY + 1); std::cout << layer1;
    setCursor(0, startY + 2); std::cout << layer2;
    setCursor(0, startY + 3); std::cout << layer3;
    setCursor(0, startY + 4); std::cout << layer4;
    setCursor(0, startY + 5); std::cout << layer5;
    setCursor(0, startY + 6); std::cout << layer6;
}
void Game::choiceStartPlayer(int diff) {
    Difficulty selectedDiff;
    if (diff == 1) selectedDiff = Difficulty::EASY;
    else if (diff == 2) selectedDiff = Difficulty::NORMAL;
    else if (diff == 3) selectedDiff = Difficulty::HARD;
    else selectedDiff = Difficulty::DEBUG_MOD;
    player = charManager.getRandomPlayer(selectedDiff);
    system("cls");
    MyString text = "Мы нашли персонажа, который сейчас находится во сне. Это ";
    output(text);
    setColor(5, 15);
    output(player.getName()); setColor(0, 15); std::cout << ". "; output(player.desc);
    drawMedievalTown(7);
    drawPlayerCard(player, 5, 15);
    std::cout << "\nНажмите любую клавишу, чтобы начать приключение..." << std::endl;
    _getch();
}

//выбор рандомной миссии + текст для игрока о цели
void drawCastle(int startY) {
    const char* l0 = R"(             |>>>           |>>>             )";
    const char* l1 = R"(             |              |                )";
    const char* l2 = R"(         _  _|_  _      _  _|_  _            )";
    const char* l3 = R"(        | |_| |_| |    | |_| |_| |           )";
    const char* l4 = R"(        |_   _   _|    |_   _   _|           )";
    const char* l5 = R"(          | | |_________| | |                )";
    const char* l6 = R"(          | |_|         |_| |      /|        )";
    const char* l7 = R"(          |  _   _____   _  |    _|_|_       )";
    const char* l8 = R"(          | | | |     | | | |   |     |      )";
    const char* l9 = R"(__________| |_|_|_____|_|_| |___|_____|______ )";

    const char* layers[] = { l0, l1, l2, l3, l4, l5, l6, l7, l8, l9 };
    setColor(12, 15);
    setCursor(0, startY); std::cout<<layers[0];
    setColor(8, 15);
    for (int i = 1; i < 9; i++) {
        setCursor(0, startY + i);
        std::cout<< layers[i];
    }
    setColor(6, 15);
    setCursor(0, startY+9); std::cout<< layers[9];
}
void drawForest(int startY) {
    setColor(2, 15);
    const char* l0 = R"(      ^  ^  ^                   ^      ^     )";
    const char* l1 = R"(     / \/ \/ \      ^          / \    / \    )";
    const char* l2 = R"(    / \/ \/ \/ \   / \        / \ \  / \ \   )";
    const char* l3 = R"(   / \/ \/ \/ \ \ / \ \      / \ \ \/ \ \ \  )";
    const char* l4 = R"(  /_ \/_ \/_ \/_ \/_ \ \    /_ \/_ \/_ \/_ \ )";
    const char* l5 = R"(    || || || || ||  ||        || || || ||    )";
    const char* l6 = R"(^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^)";

    const char* layers[] = { l0, l1, l2, l3, l4, l5, l6 };
    for (int i = 0; i < 5; i++) {
        setCursor(0, startY + i);
        std::cout<<layers[i];
    }
    setColor(6, 15);
    setCursor(0, startY + 5);
    std::cout << layers[5];
    setColor(2, 15);
    setCursor(0, startY + 6);
    std::cout << layers[6];
}
void displayLocationArt(const MyString& locName) {
    if (locName == "Замок") {
        drawCastle(10);
    }
    else if (locName == "Лес") {
        drawForest(10);
    }
    setColor(0, 15);
}
void Game::drawingMissionAndLocation() {
    currentMission = locManager.getRandomMission();
    currentLocation = locManager.getLocationByTag(currentMission.targetLocation);
    system("cls");
    setColor(0, 15);
    output(currentMission.description);
    std::cout << std::endl;
    setColor(1, 15); output(" Ваша цель: "); output(currentMission.name);
    std::cout << std::endl;
    setColor(8, 15);
    displayLocationArt(currentLocation.getName());
    std::cout << std::endl;
    MyString text = "Прежде чем вы пойдете в ";output(text); output(currentLocation.getName());
    MyString text1 = " вам надо подготовится.";  output(text1);
    std::cout << std::endl;
    MyString text2 = "Идите на рынок выберите нужные вам вещи.";
    output(text2);
    std::cout << std::endl<<std::endl;
    MyString text4 = "Упс, кажется у вас нет денег... Может удастся что-нибудь стащить?";  output(text4);
    std::cout << std::endl;
    setColor(2, 15);
    MyString text3="Увидимся в конце игры.Удачи!";
    output(text3);
    std::cout << std::endl;
    setColor(4, 15);
    std::cout << "[ Нажмите, чтобы отправиться в магазин ]";
    setColor(0, 15);
    system("pause > nul");
}

//отрисовка магазинов + логика с торговцами
void ShopArt(int startX, int startY, int color, int number) {
    const char* art = nullptr;
    switch (number) {
    case 0: art = R"(   [ ЛАВКА СТАРИКА ]
       _______
      /|=====|\
  -__/_|_____|_\__-
  /_-  0  0  0  -_\
   | |^ _ ^ _ ^| |
   0 | [X] [X] | 0
  ___|_________|___)"; break;
    case 1: art = R"(   [ ЛАВКА ДЕВИЦЫ ]
      _______
     /  ^ ^  \
   _/_________\_
  |=============|^
  - |[] (=) []| - \
    |__< I >__|/___\
  __|||_____|||__|)"; break;
    case 2: art = R"(   [ ЛАВКА ВЕДЬМЫ ]
      _______   ____
    _|  % %  |_ [**]
   /__________\--||
    |..........==||
    |  ^   ^  |  ||
    | {c} {c} |__|| *
  /\|__|___|__|==||_|)"; break;
    case 3: art = R"( [ ЛАВКА ТОРГОВЦА ]
      _______
     -/_{@}_\-
       |___|
  ===__|___|__===
   _|_[]___[]_|_
  /_| [#]_[#] |_\
 ## |__|___|__| ##)"; break;//иностранного торговца
    case 4: art = R"(
      _________|\
      \          \
        [ space ]
      /________  /
               |/)"; break;
    }
    if (!art) return;
    setColor(color, 15);
    int currentY = startY;
    setCursor(startX, currentY);

    for (int i = 0; art[i] != '\0'; ++i) {
        if (art[i] == '\n') {
            currentY++;
            setCursor(startX, currentY);
        }
        else {
            std::cout << art[i];
        }
    }
}
void Game::drawingInShop(int number) {
    system("cls");
    int StartX = 3;
    int StartY = 0;
    setCursor(StartX + 40, StartY + 2);
    MyString NameShopman = shopManager.GetNameShopman(number);
    std::cout << "[ " << NameShopman << " ]"; 
    setColor(0, 15);
    setCursor(StartX, StartY);
    for (int i = 0; i < 92; i++) std::cout << "=";
    for (int i = 1; i < 30; i++) {
        setCursor(StartX, StartY + i);
        std::cout << "||";
    }
    for (int i = 1; i < 29; i++) {
        setCursor(StartX+90, StartY + i);
        std::cout << "||";
    }  
    int color1 = 12;
    int color2 = 0;
    if (shopManager.isVisit[number]) {
        color1 = 0;
        color2 = 8;
    }
    setCursor(StartX, StartY + 29);
    for (int i = 0; i < 92; i++) std::cout << "=";
    MyVector <MyString> GetArtShopman;
    GetArtShopman = shopManager.GetArtShopman((ShopType)number);
    for (int i = 0; i < GetArtShopman.getSize(); i++) {
       setCursor(StartX + 50, StartY + 5+i);
       std::cout << GetArtShopman[i];
    }
    if (shopManager.isVisit[number] && shopManager.callCount[number] > 0) {
        MyString SpecialDialog = shopManager.GetNotActiveShopDialog((ShopType)number, shopManager.callCount[number] - 1);
        setCursor(StartX + 50, StartY + 12);
        StartY += 12;
        setColor(0, 15);
        printWrapped(SpecialDialog,StartX+50,StartY,40,20);
        StartY -= 12;
        shopManager.callCount[number]++;
    }
    else if (!shopManager.isVisit[number]) {
        MyString dialog = shopManager.GetSpecualDialogues(player.getStats(), (ShopType)number);
        StartY += 12;
        setColor(12, 15);
        printWrapped(dialog, StartX + 50, StartY, 40, 20);
        setColor(0, 15);
        StartY -= 12;
        shopManager.isVisit[number] = true;
        shopManager.callCount[number] = 1;
    }
    else {
        MyString dialog = shopManager.GetSpecualDialogues(player.getStats(), (ShopType)number);
        StartY += 12;
        setColor(2, 15);
        printWrapped(dialog, StartX + 50, StartY, 40, 20);
        setColor(0, 15);
        StartY -= 12;
        shopManager.callCount[number] = 1;
    }
    int selected = 0;
    bool inThisShop = true;
    
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info = { 100, FALSE };
    SetConsoleCursorInfo(consoleHandle, &info);
    if (!shopManager.hasInventory[number]) {
        int randCount = rand() % (10 - 3 + 1) + 3;
        if (randCount > 7) randCount = rand() % (10 - 3 + 1) + 3;
        else if(randCount<4)randCount = rand() % (10 - 3 + 1) + 3;
        shopManager.shopInventories[number] = itemManager.getRandomItemChoices(randCount, (ShopType)number);
        shopManager.hasInventory[number] = true;
    }
    MyVector<Item>& itemsMenu = shopManager.shopInventories[number];
    int visible = rand() % (shopManager.shopInventories->getSize()-1 - 1 + 1) + 1;
    MyVector <Item> tempInventory;
    bool shopManVisit = false;
    while (inThisShop) {
        for (int i = 0; i < itemsMenu.getSize(); ++i) {
            setCursor(3, 10 + i*2);
            if (i == selected) {
                setColor(color2, color1);
                std::cout << " " << itemsMenu[i].getName() << " "<<std::endl;
                setColor(8, 15);
                std::cout<< itemsMenu[i].getDescription();
                setColor(0, 15);
            }
            else {
                setColor(0, 15);
                std::cout << " " << itemsMenu[i].getName()<<" " << std::endl;
                std::cout << "                                                    ";
            }
        }

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) selected = (selected - 1 + itemsMenu.getSize()) % itemsMenu.getSize();
            else if (key == 80) selected = (selected + 1) % itemsMenu.getSize();
        }
        else if (key == 13) {
            if (visible && shopManager.isVisit[number] && shopManager.callCount[number] <= 1) {
                tempInventory.push_back(itemsMenu[selected]);
                std::cout << "[ Экипирован предмет " << itemsMenu[selected].getName() << " ]     ";
                visible--;
            }
            else if (visible <= 0) {
                setColor(12, 15); std::cout<<std::endl << "[ Торговец увидел, что вы украли предмет! Он забрал все вещи которые вы взяли ]";
                tempInventory.clear(); 
                shopManVisit = true;
            }
            else {
                std::cout << "[ Вам не хотят продавть ничего! ]       ";   
                shopManVisit = true;
            }
            shopManager.itemEquiped[number] = true;
            if (shopManVisit) {
                 color1 = 0;
                 color2 = 8;
            }
            
        }
        else if (key == 27) {
            if (tempInventory.getSize()) {
                for (int i = 0;i < tempInventory.getSize();i++) {
                    player.equipItem(tempInventory[i]);
                }
            }
            inThisShop = false;
            system("cls");
            drawingShop();
        }
        
    }
}
void Game::drawingShop() {
    int selected = 0;
    bool inShop = true;

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info = { 100, FALSE };
    SetConsoleCursorInfo(consoleHandle, &info);
    system("cls");
    while (inShop) {
        setCursor(0,0);

        int startX = 3;
        int startY = 5;
        int step = 25; 

        for (int i = 0; i < 4; ++i) {
            int color;
            switch (i) {
            case 0: color = 1; break;
            case 1: color = 5; break;
            case 2: color = 2; break;
            case 3: color = 6; break;
            case 4: color = 12; break;
            default: color = 7;
            }
            ShopArt(startX + i * step, startY, color, i);
        }
        ShopArt(startX + 3 * step-10, startY+20, 12, 4);
        int arrowX = startX + (selected * step) + 10;
        int arrowY = startY + 10;
        setCursor(0, arrowY);
        int color2 = 12;
        std::cout << "                                                                                          ";
        std::cout << "                                                                                          ";
        std::cout << "                                                                                          ";
        setCursor(arrowX, arrowY);
        if (shopManager.isVisit[selected]) color2 = 0;
        setColor(color2, 15);
        std::cout << "^";

        setCursor(arrowX - 5, arrowY + 1);
        std::cout << "[ Enter ]";

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 75) selected = (selected - 1 + 4) % 4;
            else if (key == 77) selected = (selected + 1) % 4;
        }
        else if (key == 13) {
            inShop = false;
            drawingInShop(selected);
        }
        else if (key == 32) {
            inShop = false;
            setColor(0, 15);
            system("cls");
        }
    }
}

//локация + пути выбора + проигрышь
void Game::inLocation() {
    MyString text1 = "Продавцы в этом месте не всегда дружелюбны. Но это не важно я прибыл на место. Вот и ";
    output(text1);
    setColor(2, 15);
    MyString text2 = currentLocation.getName();
    output(text2);
    setColor(0, 15);
    displayLocationArt(text2);    
    std::cout << std::endl;
    MyString text3 = currentLocation.getDescription();
    output(text3);
    int StartX=50, StartY=10;
    setCursor(StartX, StartY);

    MyVector <MyString> menuItems = currentLocation.getAllNamePath();
    int selected = 0;
    bool inMenu = true;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
    while (inMenu) {
        for (int i = 0; i < menuItems.getSize(); ++i) {
            setCursor(StartX, StartY + i);
            if (i == selected) {
                setColor(0, 12);
                std::cout << " " << menuItems[i] << " ";
                setColor(0, 15);
            }
            else {
                setColor(0, 15);
                std::cout << " " << menuItems[i] << " ";
            }
        }
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) selected = (selected - 1 + menuItems.getSize()) % menuItems.getSize();
            else if (key == 80) selected = (selected + 1) % menuItems.getSize();
        }
        else if (key == 13) {
            info.bVisible = TRUE;
            SetConsoleCursorInfo(consoleHandle, &info);
            inMenu = false;
            system("cls");
            MyString text4 = currentLocation.FailOrWin(player, selected);
            bool isWin = currentLocation.checkPath(player, selected);
            int color = 12;
            if (isWin) {
                color = 2;
            }
            setColor(color, 15);
            output(text4);
            setColor(0, 15);
            if (!isWin) {
                MyString text5 = "Кажется это конец может стоило выбрать другой выбор?";
                output(text5);

                MyVector <MyString> menuItem;
                menuItem.push_back("Выбрать другой путь");
                menuItem.push_back("Закончить игру");
                int s = 0;
                bool inMen = true;
                HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_CURSOR_INFO info;
                info.dwSize = 100;
                info.bVisible = FALSE;
                SetConsoleCursorInfo(consoleHandle, &info);
                while (inMen) {
                    for (int i = 0; i < menuItem.getSize(); ++i) {
                        setCursor(StartX-20, StartY + i);
                        if (i == s) {
                            setColor(0, 12);
                            std::cout << " " << menuItem[i] << " ";
                            setColor(0, 15);
                        }
                        else {
                            setColor(0, 15);
                            std::cout << " " << menuItem[i] << " ";
                        }
                    }
                    int key = _getch();
                    if (key == 224) {
                        key = _getch();
                        if (key == 72) s = (s - 1 + menuItem.getSize()) % menuItem.getSize();
                        else if (key == 80) s = (s + 1) % menuItem.getSize();
                    }
                    else if (key == 13) {
                        info.bVisible = TRUE;
                        SetConsoleCursorInfo(consoleHandle, &info);
                        inMen = false;
                        system("cls");
                        switch (s) {
                        case 0: inLocation(); break;
                        case 1: exit(0); break;
                        }
                    }
                }
            }
            player.applyStatChange(currentLocation.paths[selected].rewards);
        }
    }
}

//случайные вещи брать или не брать на что менять?
void Game::findItem() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    int callFindItems = rand() % (5 - 2 + 1) + 2;
    std::cout << std::endl;
    MyString text1 = "Наконец-то я на месте. Самое время занятся делом. Так что здесь есть. Надо оглядется.";
    output(text1);
    MyString text2 = "Я что-то нашел. Жаль, что у меня нет места. Я не могу тащить весь хлам с собой. Стоит ли это брать с собой? Я могу взять предмет заменив его на другой. Что это?";std::cout << std::endl; 
    output(text2);setColor(12, 15);
    bool inMenuFind = true;
    int StartY = 5;
    MyString tag = currentLocation.getName();
    while (inMenuFind) {       
        if (callFindItems <= 0) inMenuFind = false;
        Item tempItem = itemManager.generateRandomFoundItem(tag);
        setColor(0, 15);
        setCursor(0, StartY);StartY += 5;
        std::cout << std::endl; output(tempItem.name);std::cout << std::endl;
        setColor(8, 15);
        output(tempItem.description);
        std::cout << std::endl;std::cout << std::endl;
        MyVector <MyString> playerItems = player.getItemsBySlot(tempItem.getSlotType());
        playerItems.push_back("Не менять"); int inChoice=true; int selected=0;
        while (inChoice) {
            setColor(0, 50);
            for (int i = 0; i < playerItems.getSize(); ++i) {
                setCursor(60, 20+i);
                if (i == selected) {
                    setColor(0, 12);
                    std::cout << " " << playerItems[i] << " ";
                    setColor(0, 15);
                }
                else {
                    setColor(0, 15);
                    std::cout << " " << playerItems[i] << "        ";
                }
            }
            int key = _getch();
            if (key == 224) {
                key = _getch();
                if (key == 72) selected = (selected - 1 + playerItems.getSize()) % playerItems.getSize();
                else if (key == 80) selected = (selected + 1) % playerItems.getSize();
            }
            else if (key == 13) {
                if (selected < (playerItems.getSize()-1)) {               
                    Item* ptr = itemManager.findItemByName(playerItems[selected]);
                    Item unItem;
                    if (ptr) {
                        unItem = *ptr;
                    }
                    player.unEquipItem(unItem);
                    player.equipItem(tempItem);
                    setColor(0, 15);       
                    setCursor(0, StartY - 2);
                    std::cout << std::endl; std::cout << "[    Подобран предмет    ]  ";
                    std::cout <<std::endl<< "_________________________________________";
                    callFindItems--;
                    inChoice = false;
                }
                if (selected == (playerItems.getSize() -1)) {
                    inChoice = false;
                    setCursor(0, StartY - 2);
                    std::cout << std::endl; std::cout << "[    Предмет не подобран  ]  ";
                    std::cout << std::endl << "_________________________________________";
                    callFindItems--;
                }
            }
        }
    }
}

//случайное событие + выбор
void specialOutput(MyString Text, MyString Name) {
    bool skip = false;
    int count = 1;
    for (int i = 0; i < Text.size(); i++) {
        if (Text[i] == '|') { 
            count++;
            std::cout << std::endl; 
            if (count % 2==0) {
                output(Name);std::cout << ":";
            }     
            continue;
        }
        std::cout << Text[i] << std::flush;
        if (!skip) {
            if (_kbhit()) {
                _getch();
                skip = true;
            }
            Sleep(60);
        }
    }
}
void Game::eventMeeting() {
    system("cls");
    setColor(0, 15);
    MyString text1 = "Мне нужно выполнить миссию надеюсь никто не помешает мне...";
    output(text1); std::cout << std::endl;
    currentEvent = locManager.getRandomEventByType(currentLocation.getName());
    MyString text3 = currentEvent.getDescription();
    output(text3);
    int StartX = 10, StartY = 10;
    setCursor(StartX, StartY);

    MyVector <MyString> menuItems = currentEvent.getAllNamePath();
    int selected = 0;
    bool inMenu = true;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
    while (inMenu) {
        for (int i = 0; i < menuItems.getSize(); ++i) {
            setCursor(StartX, StartY + i);
            if (i == selected) {
                setColor(0, 9);
                std::cout << " " << menuItems[i] << " ";
                setColor(0, 15);
            }
            else {
                setColor(0, 15);
                std::cout << " " << menuItems[i] << " ";
            }
        }
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) selected = (selected - 1 + menuItems.getSize()) % menuItems.getSize();
            else if (key == 80) selected = (selected + 1) % menuItems.getSize();
        }
        else if (key == 13) {
            info.bVisible = TRUE;
            SetConsoleCursorInfo(consoleHandle, &info);
            inMenu = false;
            system("cls");
            MyString text4 = currentEvent.FailOrWin(player, selected);
            bool isWin = currentEvent.checkPath(player, selected);
            int color = 2;
            if (isWin) {
                color = 12;
            }
            setColor(color, 15);
            specialOutput(text4,player.getName());
            setColor(0, 15);
            if (isWin) {
                player.applyStatChange(currentEvent.paths[selected].rewards);
            }  
        }
    }
}

//крафт предметов по рецепту
void Game::craftBlock() {
    std::cout << std::endl;
    output("Пора готовиться к моей миссии. Посмотрим, что у меня есть. Может я смогу их как-то использовать? Что если соеденить ");
    setColor(5, 15); output("несколько редметов?");
    setColor(0, 15);output("Для выбора "); setColor(11, 15);output("Enter");
    setColor(0, 15); output(". Для крафта "); setColor(13, 15); output("E.");
    setColor(0, 15); output("Для выхода из графта "); setColor(4, 15); output("SPACE");
    setColor(0, 15);
    MyVector <Item> menuItems = player.getInventory();
    int StartX = 10, StartY = 10;
    int selected = 0;
    bool inMenu = true;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
    MyVector <Item> itemsForCraft;
    int countItem = 0;

    while (inMenu) {
        for (int i = 0; i < menuItems.getSize(); ++i) {
            setCursor(StartX, StartY + i);
            if (i == selected) {
                setColor(0, 9);
                std::cout << " " << menuItems[i].getName() << " ";
                setColor(0, 15);
            }
            else {
                setColor(0, 15);
                std::cout << " " << menuItems[i].getName() << " ";
            }
        }
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) selected = (selected - 1 + menuItems.getSize()) % menuItems.getSize();
            else if (key == 80) selected = (selected + 1) % menuItems.getSize();
        }
        else if (key == 13) {
            if (countItem > 0) { 
                setCursor(StartX + 20, StartY + 5 + countItem * 2+1);
                std::cout << "+";
            }
            countItem++;
            itemsForCraft.push_back(menuItems[selected]);
            setCursor(StartX + 20, StartY+5 +countItem*2);
            std::cout << menuItems[selected].getName();       
        }
        else if (key == 101 || key == 69 || key == 227 || key == 133) {
            if (itemsForCraft.getSize() == 0) continue;
            const StoryCombo* comboPointer = comboManager.checkAllCombos(itemsForCraft);
            setCursor(StartX + 20, StartY + 5 + (countItem * 2) + 1);
            std::cout << "=";
            MyString textAfterCraft = "Хм... Ничего не вышло?";

            if (comboPointer != nullptr) {
                if (comboPointer->statusThreshold <= player.getStatValue("status")) {
                    for (int k = 0; k < itemsForCraft.getSize(); k++) {
                        player.unEquipItem(itemsForCraft[k]);
                    }
                    player.applyStatChange(comboPointer->rewards);
                    textAfterCraft = comboPointer->successText;
                }
                else {
                    textAfterCraft = comboPointer->failText;
                }
            }
            setCursor(StartX + 20, StartY + 5 + (countItem * 2) + 2);
            setColor(3, 15);
            StartY += 5 + (countItem * 2) + 2;
            printWrapped(textAfterCraft, StartX + 20, StartY, 40, 10);
            StartY -= 5 + (countItem * 2) + 2;
            setColor(0, 15);
            _getch();
            for (int i = 0; i <= countItem * 2 + 2; ++i) {
                clearLine(StartX + 20, StartY + 5 + i, 60);
            }
            menuItems = player.getInventory();
            selected = 0;
            for (int i = 0; i < 20; i++) clearLine(StartX, StartY + i, 20);
            itemsForCraft.clear();
            countItem = 0;
        }
        else if (key == 32) {
            info.bVisible = TRUE;
            SetConsoleCursorInfo(consoleHandle, &info);
            inMenu = false;
            system("cls");
        }
    } 
}

void Game::final() {
    system("cls");
    setColor(0, 15);
    MyString text1 = "И вот я добрался к цели.", text2=" Но мне нужен план.Что делать ? ";
    output(text1); output(currentMission.secondDescription); std::cout << std::endl; output(text2);
    int StartX = 10, StartY = 10;
    setCursor(StartX, StartY);

    MyVector <MyString> menuItems = currentMission.getAllNamePath();
    int selected = 0;
    bool inMenu = true;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
    while (inMenu) {
        for (int i = 0; i < menuItems.getSize(); ++i) {
            setCursor(StartX, StartY + i);
            if (i == selected) {
                setColor(0, 12);
                std::cout << " " << menuItems[i] << " ";
                setColor(0, 15);
            }
            else {
                setColor(0, 15);
                std::cout << " " << menuItems[i] << " ";
            }
        }
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) selected = (selected - 1 + menuItems.getSize()) % menuItems.getSize();
            else if (key == 80) selected = (selected + 1) % menuItems.getSize();
        }
        else if (key == 13) {
            info.bVisible = TRUE;
            SetConsoleCursorInfo(consoleHandle, &info);
            inMenu = false;
            system("cls");
            MyString text4 = currentMission.FailOrWin(player, selected);
            bool isWin = currentMission.checkPath(player, selected); int color = 2;
            if (!isWin) color = 12; setColor(color, 15);output(text4);setColor(0, 15);
            if (!isWin) {
                std::cout << std::endl;
                MyVector <MyString> menuItem;
                menuItem.push_back("Выбрать другой путь");
                menuItem.push_back("Закончить игру");
                int s = 0;
                bool inMen = true;
                HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_CURSOR_INFO info;
                info.dwSize = 100;
                info.bVisible = FALSE;
                SetConsoleCursorInfo(consoleHandle, &info);
                while (inMen) {
                    for (int i = 0; i < menuItem.getSize(); ++i) {
                        setCursor(StartX - 20, StartY + i);
                        if (i == s) {
                            setColor(0, 12);
                            std::cout << " " << menuItem[i] << " ";
                            setColor(0, 15);
                        }
                        else {
                            setColor(0, 15);
                            std::cout << " " << menuItem[i] << " ";
                        }
                    }
                int key = _getch();
                if (key == 224) {
                    key = _getch();
                    if (key == 72) s = (s - 1 + menuItem.getSize()) % menuItem.getSize();
                    else if (key == 80) s = (s + 1) % menuItem.getSize();
                }
                else if (key == 13) {
                    info.bVisible = TRUE;
                    SetConsoleCursorInfo(consoleHandle, &info);
                    inMen = false;
                    system("cls");
                    switch (s) {
                    case 0: final(); break;
                    case 1: exit(0); break;
                    }
                 }
                }
            }
            
        }
    }
}

void Game::loadGame() {}
void Game::showStory() {}