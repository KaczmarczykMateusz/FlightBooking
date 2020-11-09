/*
 * FlightManager.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_FLIGHTMANAGER_HPP_
#define APPLICATION_FLIGHTMANAGER_HPP_

#include "../File/FlightFile.hpp"

#include <sstream>

class FlightManager {
public:
	FlightManager() = default;

	uint8_t MainMenu();
	void DisplayAllRecords();  //TODO: change to get records and display them in another function
	void Book();
	void Search();
	void RegisterNew();  //TODO: consider returning error codes
	void ChooseAction(uint8_t mainChoice);
	UserInterface & GetUI();

private:
	enum CHOICE {
		BOOK = 1,
		CHECK_IN,
		SEARCH,
		SHOW_SCHEDULE,
		REGISTER,
		DELETE,
		EXIT
	};

	UserInterface UI;
	FlightFile File;

	uint32_t GetGreatestFlightNo();
};


#endif /* APPLICATION_FLIGHTMANAGER_HPP_ */
