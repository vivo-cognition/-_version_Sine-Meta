#pragma once
#include "Shopman.h"
#include "Enum.h"
#include "Item.h"
struct ShopmanManager {
	MyVector <MyVector <MyString>> allShopMansArt;
    Shopman allDialogues[4];
	MyString shopmansArtFilePath;
	MyString dialoguesFilePath;
	int callCount[4];
	bool isVisit[4];
	MyVector<Item> shopInventories[4];
	bool hasInventory[4];
	bool itemEquiped[4];

	ShopmanManager(const MyString& shopmansArt="ArtShopman.txt", 
		const MyString& dialogPath = "ShopDialogues.txt");

	bool loadDialogsFromTxt();
	bool loadShopmansFromTxt();

	MyString GetSpecualDialogues(const StatVector& statsPlayer, ShopType shop);
	MyString GetNotActiveShopDialog(ShopType type, int number);
	MyVector <MyString> GetArtShopman (ShopType type);
	MyString GetFinalDialogues(ShopType shop);
	MyString GetNameShopman(int number);
};