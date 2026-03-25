#pragma once
#include "MyVector.h"
#include "Location.h"

struct LocationManager {
	MyVector<Location> allLocations;
	MyVector<Location> eventPool;
	MyString locationsFilePath;
	MyString eventsFilePath;

	LocationManager(const MyString& locPath = "Locations.txt",
		const MyString& evPath = "Events.txt");

	bool loadLocationsFromTxt();
	bool loadEventsFromTxt();

	Location getRandomEventByType(const MyString& type);
   
	bool isLoaded() const;
	const MyVector<Location>& getAllLocations() const;
	void printAllLocations() const;
    Location getRandomLocation();
	int getTotalCount() const;

};

