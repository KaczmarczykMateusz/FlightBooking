/*
 * FlightManager.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
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
	void displayAllRecords();  //TODO: change to get records and display them in another function
	void book();
	bool searchByAirports();
	void registerNew();  //TODO: consider returning error codes
	void chooseAction(uint8_t mainChoice);

private:
	UserInterface UI;
	ScheduleFile scheduleFile;

	uint32_t getGreatestFlightNo();
};


#endif /* APPLICATION_FLIGHTMANAGER_HPP_ */
