#pragma once
#include "MyVector.h"
#include "Location.h"

struct LocationManager {
	MyVector<Location> allLocations;
	MyVector<Location> eventPool;
	MyString locationsFilePath;
	MyString eventsFilePath;
	Location kingFinal;
	MyString kingFilePath;

	LocationManager(const MyString& locPath = "Locations.txt",
		const MyString& evPath = "Events.txt", const MyString& kinPath = "KingFinal.txt");

	bool loadLocationsFromTxt();
	bool loadEventsFromTxt();
	bool loadKingFinalFromTxt();

	Location getRandomEventByType(const MyString& type);
   
	bool isLoaded() const;
	const MyVector<Location>& getAllLocations() const;
	void printAllLocations() const;
    Location getRandomLocation();
	int getTotalCount() const;

};

