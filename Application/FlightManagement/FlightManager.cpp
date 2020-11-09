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

using std::ostream;

uint8_t FlightManager::MainMenu() {
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

		UI.Display(text.str());
		std::string input(1, '\0');
		//TODO: find solution for below
//			getline(cin, input); //In debug session input is not clear and this eats cin buffer//TODO: check why
		getline(std::cin, input);

		try {
			choice = std::stoul(input);
		}
		catch(...) {
			choice = 255; //Invalid index
		}
		if(7 < choice-'0') {
			//TODO: consider to replace new lines with console clearing
			text << "\n\nInvalid number, please enter right digit\n\n"
				 << "\n\n\n Entered digit:   " << choice << std::endl;
			UI.Display(text.str());
		}
	} while(7 < (choice-'0'));
	return choice;
}

uint32_t FlightManager::GetGreatestFlightNo() {
	uint32_t rc = File.SearchGreatestNo();
	if(!rc) {
		UI.Display("FAIL SEARCHING FOR NUMBER \n");
	}
	return rc;
}

void FlightManager::DisplayAllRecords() {
	uint8_t getIndex = 1;
	std::string record;
	while(File.GetRecord(record, getIndex)) {
		Flight flight(record);
		std::ostringstream flightStream;
		flight.Print(flightStream);
		UI.Display(flightStream.str());

		getIndex += 1;
	}
}

void FlightManager::Book() {
	Search();
	//TODO: continue with booking
}

void FlightManager::Search() {
	std::string depatrureCity = UI.GetDepartureCity();
	std::string arrivalCity = UI.GetArrivalCity();

	std::vector<Flight> flights = File.SearchFlight(depatrureCity, arrivalCity);

	if(!flights.empty()) {
		UI.Display(FlightHeader);
		for(auto flight : flights) {
			std::ostringstream flightInfo;
			flight.Print(flightInfo);
			UI.Display(flightInfo.str());
		}
	} else {
		UI.Display("Not found \n");
	}
}

void FlightManager::RegisterNew() {
	std::string numberStr(NUMBER_LENGTH + 1, ' ');
	uint32_t flightNo = GetGreatestFlightNo() + 1;

	std::string company = UI.GetCompany();
	std::string departureCity = UI.GetDepartureCity();
	std::string arrivalCity = UI.GetArrivalCity();
	std::string date = UI.GetDate();

	std::string record = UI.FormatLine(flightNo, company, departureCity, arrivalCity, date);

	File.WriteFlights(record, RECORD_LENGTH);
}

void FlightManager::ChooseAction(uint8_t mainChoice) {
	switch(mainChoice) {
	case BOOK:
		Book();
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
		Search();
		break;
	case SHOW_SCHEDULE:
		DisplayAllRecords();
		break;
	case REGISTER:
		RegisterNew();
		break;
	case DELETE:
		assert(0); //TODO: fill case
		break;
	case EXIT:
		break;
	default:
		assert(0);
	}
}

UserInterface & FlightManager::GetUI() {
	return UI;
}
