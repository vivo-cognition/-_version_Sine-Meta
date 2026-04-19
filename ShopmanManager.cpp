#define _CRT_SECURE_NO_WARNINGS
#include "ShopmanManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

ShopmanManager::ShopmanManager(const MyString& shopmansArt, const MyString& dialogPath) :
	shopmansArtFilePath(shopmansArt), dialoguesFilePath(dialogPath) {
	for (int i = 0; i < 4; i++) {
		isVisit[i] = false;
		callCount[i] = 0;
		itemEquiped[i] = false;
	}
	for (int i = 0; i < 4; i++) {
		hasInventory[i] = false;
	}
	loadDialogsFromTxt();
 	loadShopmansFromTxt();
}
bool ShopmanManager::loadDialogsFromTxt() {
	FILE* file = fopen(dialoguesFilePath.c_str(),"r");
	if (!file) {
		printf("ÎØÈÁÊÀ: Ôàéë %s íå íàéäåí\n", dialoguesFilePath.c_str());
		return false;
	}
	char line[256];
	while (fgets(line, sizeof(line), file)) {
		if (line[0] == '}' || line[0] == '\n' || line[0] == '\r') continue;
		char cleanName[50];
		sscanf(line, "%s", cleanName);
		ShopType currentShop = Shopman::MyStringToShopType(cleanName);

		MyVector <MyString> Dialoges;
		for (int j = 0; j < 3;j++) {
			if (!fgets(line, sizeof(line), file)) break;
			line[strcspn(line, "\r\n")] = 0;
			MyString dialog = line;
			Dialoges.push_back(dialog);
		}
		if (!fgets(line, sizeof(line), file)) break;
		line[strcspn(line, "\r\n")] = 0;
		MyString close = line;

		if (!fgets(line, sizeof(line), file)) break;
		int statsCount = atoi(line);

		StatVector shopStats(statsCount);
		for (int j = 0; j < statsCount; j++) {
			char statName[50];
			int statValue;
			if (fscanf(file, "%s %d", statName, &statValue) == 2) {
				shopStats.setAt(j, MyString(statName), statValue);
			}
		}
		fscanf(file, "%*[\n\r]");
		MyVector <MyString> special;
		for (int k = 0; k < statsCount;k++) {
			if (!fgets(line, sizeof(line), file)) break;
			line[strcspn(line, "\r\n")] = 0;
			MyString Sdialog = line;
			special.push_back(Sdialog);
		}

		Shopman newShop(currentShop, Dialoges, close, shopStats,special);
		allDialogues[(int)currentShop] = newShop;
	}
	fclose(file);
	return true;
}
bool ShopmanManager::loadShopmansFromTxt() {
	FILE* file = fopen(shopmansArtFilePath.c_str(), "r");
	if (!file) {
		printf("ÎØÈÁÊÀ: Ôàéë %s íå íàéäåí\n", shopmansArtFilePath.c_str());
		return false;
	}
	char line[256];
	while (fgets(line, sizeof(line), file)) {
		if (!fgets(line, sizeof(line), file)) break;
		int strCount = atoi(line);
		int i = 0;
		MyVector <MyString> OneArt;
		for (int j = 0; j < strCount; j++) {
			if (!fgets(line, sizeof(line), file)) break;
			line[strcspn(line, "\r\n")] = 0;
			MyString str = line;
			OneArt.push_back(str);
		}
		allShopMansArt.push_back(OneArt);
		i++;
	}
	fclose(file);
	return true;
}
MyVector <MyString> ShopmanManager::GetArtShopman(ShopType type) {
	int index = (int)type;
	if (index > 3 || index < 0) {
		return MyVector <MyString>();
	}
	return allShopMansArt[index];
}
MyString ShopmanManager::GetFinalDialogues(ShopType shop) {
	int index = (int)shop;
	if (index > 3 || index < 0) {
		return MyString();
	}
	return allDialogues[index].CloseShop;
}
MyString ShopmanManager::GetNotActiveShopDialog(ShopType type, int number) {
	int index = (int)type;
	if (index > 3 || index < 0) {
		return MyString();
	}
    return allDialogues[index].Dialogs[number];
}
MyString ShopmanManager::GetSpecualDialogues(const StatVector& statsPlayer, ShopType shop) {
	const Shopman& currentShopman = allDialogues[(int)shop];
	for (int i = 0; i < statsPlayer.size; i++) {
		StatPair playerStat = statsPlayer.getAt(i);
		for (int j = 0; j < currentShopman.Stat.size; j++) {
			StatPair shopStat = currentShopman.Stat.getAt(j);
			if (playerStat.key == shopStat.key && playerStat.value >= shopStat.value) {
				if (j < currentShopman.SpecialDialogs.getSize()) {
					return currentShopman.SpecialDialogs[j];
				}
			}
		}
	}
	return currentShopman.SpecialDialogs.getSize() > 0 ? currentShopman.SpecialDialogs[0] : MyString("...");
}
MyString ShopmanManager::GetNameShopman(int number) {
	return  Shopman::ShopTypeToMyString(allDialogues[number].Name);
}