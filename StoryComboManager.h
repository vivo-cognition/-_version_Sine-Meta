#pragma once
#include "MyVector.h"
#include "StoryCombo.h"

struct StoryComboManager {
	MyVector<StoryCombo> allCombos;
	MyString storyCombosFilePath;

	StoryComboManager(const MyString& comPath = "Combos.txt");

	bool loadCombosFromTxt();

	const StoryCombo* checkAllCombos(const MyVector<MyString>& selectedItems) const;
	int getCombosCount() const;
};

