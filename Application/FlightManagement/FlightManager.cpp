/*
 * FlightManager.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: mateusz
 */

#include "FlightManager.hpp"

#include <cassert>
#include <iostream>
#include <vector>

#include "../Common/StringFormatter.hpp"
using std::ostream;

uint8_t FlightManager::mainMenu() {
	uint8_t choice = 0;
	do {
		std::ostringstream text;
		text << "\n"
		<< "--------------------------------------------------------\n"
		<< "***************FLIGHT CENTER POKAHONTAS****************\n"
		<< "--------------------------------------------------------\n"
		<< "What would you like to do: (chose with numeric keypad)\n"
		<< BOOK		<< " - Book new fligt            " << CHECK_IN << " - Check-in\n"
		<< SEARCH	<< " - Search flight             " << SHOW_SCHEDULE << " - Check flight schedule\n"
		<< REGISTER	<< " - Register new flight       " << DELETE << " - Delete flight\n"
		<< EXIT		<< " - Exit system\n";
		UI.display(text.str());

		std::string input(1, '\0');
		getline(std::cin, input);

		try {
			choice = std::stoul(input);
		}
		catch(...) {
			choice = 255; //Invalid index
		}
		if(7 < choice-'0') {
			text << "\n\nInvalid number, please enter right digit\n\n"
				 << "\n\nEntered digit:   " << choice << std::endl;
			UI.display(text.str());
		}
	} while(7 < (choice-'0'));
	return choice;
}

uint32_t FlightManager::getGreatestFlightNo() {
	uint32_t rc = flightsFile.searchGreatestNo();
#if DEBUG
	if(!rc) {
		UI.display("FAIL SEARCHING FOR NUMBER \n");
	}
#endif
	return rc;
}

void FlightManager::displayAllRecords() {
	uint8_t getIndex = 1;
	std::string record;
	while(flightsFile.getRecord(record, getIndex)) {
		Flight flight(record);
		std::string str = StringFormatter::formatRecordUI(flight);
		UI.display(str);

		getIndex += 1;
	}
}

void FlightManager::book() {
	searchByAirports();
	//TODO: continue with booking
}

void FlightManager::searchByAirports() {
	std::string depatrureCity = UI.getDepartureCity();
	std::string arrivalCity = UI.getArrivalCity();

	std::vector<Flight> flights = flightsFile.searchFlight(depatrureCity, arrivalCity);

	if(!flights.empty()) {
		UI.display(FlightHeader);
		for(auto flight : flights) {
			std::string str = StringFormatter::formatRecordUI(flight);
			UI.display(str);
		}
	} else {
		UI.display("Not found \n");
	}
}

void FlightManager::registerNew() {
	uint32_t flightNo = getGreatestFlightNo() + 1;

	std::string company = UI.getCompany();
	std::string departureCity = UI.getDepartureCity();
	std::string arrivalCity = UI.getArrivalCity();
	DateTime date = UI.getDateTime();

	Flight flight(flightNo, company, date, departureCity, arrivalCity, 300);

	flightsFile.registerFlight(flight);
}

void FlightManager::chooseAction(uint8_t mainChoice) {
	switch(mainChoice) {
	case BOOK:
		book();
		break;
	case CHECK_IN:
		assert(0); //TODO: fill case
		/*
		 * We will generate separate files for every flight number,
		 * they will contain passangers check-in info, file will be
		 * generated automaticallly after firt passanger check in.
		 * We will put those files i separate folder
		 */
		break;
	case SEARCH:
		searchByAirports();
		break;
	case SHOW_SCHEDULE:
		displayAllRecords();
		break;
	case REGISTER:
		registerNew();
		break;
	case DELETE:
		assert(0); //TODO: fill case
		break;
	case EXIT:
		break;
	default:
		assert(0);
	}
	UI.display("\nPress enter in order to continue");
}

