/*
 * FlightManager.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_FLIGHTMANAGER_HPP_
#define APPLICATION_FLIGHTMANAGER_HPP_

#include "../FileInterface.hpp"

#include <sstream>

class FlightManager {
public:
	FlightManager() = default;

	uint8_t MainMenu();
	void DisplayAllRecords(FileInterface & file);
	void Book();
	void Search();
	void RegisterNew();
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
	FileInterface File;

	uint32_t GetGreatestFlightNo(FileInterface & file);
};


#endif /* APPLICATION_FLIGHTMANAGER_HPP_ */
