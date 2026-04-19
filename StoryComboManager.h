#pragma once
#include "MyVector.h"
#include "StoryCombo.h"
#include "Item.h"

struct StoryComboManager {
	MyVector<StoryCombo> allCombos;
	MyString storyCombosFilePath;

	StoryComboManager(const MyString& comPath = "D:\\BSTU\\OAiP\\coursework\\Ñ_version_Sine-Meta\\Combos.txt");

	bool loadCombosFromTxt();

	const StoryCombo* checkAllCombos(const MyVector<Item>& selectedItems) const;
	int getCombosCount() const;
};

