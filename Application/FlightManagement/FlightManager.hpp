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
	void RegisterNew();
	void ChooseAction(uint8_t mainChoice);
	UserInterface & GetUI();

private:
	UserInterface UI;
	FileInterface File;

	uint32_t GeteGreatestFlightNo(FileInterface & file);
};


#endif /* APPLICATION_FLIGHTMANAGER_HPP_ */
