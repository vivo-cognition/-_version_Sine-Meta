#pragma once
#include "MyVector.h"
#include "Location.h"
#include "Mission.h"

struct LocationManager {
	MyVector<Location> allLocations;
	MyVector<Location> eventPool;
	MyVector <Mission> missionsPool;
	MyString locationsFilePath;
	MyString eventsFilePath;
	MyString missionFilePath;

	LocationManager(const MyString& locPath = "Locations.txt",
		const MyString& evPath = "Events.txt", const MyString& misPath = "Mission.txt");

	bool loadLocationsFromTxt();
	bool loadEventsFromTxt();
	bool loadMissionsFromTxt();

	Mission getRandomMission();
	Location getLocationByTag(const MyString& tag);
	Location getRandomEventByType(const MyString& type);

	bool isLoaded() const;
	const MyVector<Location>& getAllLocations() const;
	void printAllLocations() const;
	int getTotalCount() const;

};

