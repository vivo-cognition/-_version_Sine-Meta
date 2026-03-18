#pragma once
#include "MyVector.h"
#include "Location.h"

struct LocationManager {
	MyVector<Location> allLocations;
	MyString locationsFilePath;
	LocationManager(const MyString& filePath = "Locations.txt");
	bool loadLocationsFromTxt();
   
	bool isLoaded() const;
	const MyVector<Location>& getAllLocations() const;
	void printAllLocations() const;
    Location getRandomLocation();
	int getTotalCount() const;

};

