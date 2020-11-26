/*
 * FlightManager.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 *  Description: Collects data from User Interface (UI)
 *  then call functions from specific classes to handle them
 */

#ifndef APPLICATION_FLIGHTMANAGER_HPP_
#define APPLICATION_FLIGHTMANAGER_HPP_

#include "../File/ScheduleFile.hpp"

#include <sstream>

class FlightManager {
public:
	enum CHOICE {
		BOOK = 1,
		CHECK_IN,
		SEARCH,
		SHOW_SCHEDULE,
		REGISTER,
		DELETE,
		EXIT
	};

	FlightManager() = default;

	uint8_t mainMenu();
	bool showSchedule();
	bool book();
	bool checkIn();
	bool searchByAirports();
	bool registerNew();
	bool deleteFlight();
	void chooseAction(uint8_t mainChoice);

private:
	UserInterface UI;
	ScheduleFile scheduleFile;

	uint32_t getHightstId();
};


#endif /* APPLICATION_FLIGHTMANAGER_HPP_ */
