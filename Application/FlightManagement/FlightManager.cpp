/*
 * FlightManager.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: mateusz
 */

#include "FlightManager.hpp"
#include "Passenger.h"
#include "../StringFormat/ScheduleStrFormat.hpp"
#include "../File/PassengerListFile.hpp"
#include "../StringFormat/StringFormatter.hpp"

#include <cassert>
#include <iostream>
#include <vector>

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
	uint32_t rc = scheduleFile.searchGreatestNo();
#if DEBUG
	if(!rc) {
		UI.display("FAIL SEARCHING FOR NUMBER \n");
	}
#endif
	return rc;
}

bool FlightManager::displayAllRecords() {
	uint8_t getIndex = 0;
	std::string record;
	bool result = true;
	while(scheduleFile.getRecord(record, ++getIndex)) {
		Flight flight(record);
		std::string str = ScheduleStrFormat::formatRecordUI(flight);
		UI.display(str);
		if(str.empty()) {
			result = false;
		}
	}
	return result;
}

bool FlightManager::book() {
	if(!searchByAirports()) {
		return false;
	}
	std::unique_ptr<Flight> flight = nullptr;
	bool repeat = false;
	do {
		uint32_t flightId = UI.getFlightId();

		flight = scheduleFile.searchFlight(flightId);

		if(!flight) {
			repeat = UI.getRepeat();
		}
	} while(repeat);

	bool result = false;
	if(flight) {
		PassengerListFile file(flight->getId());

		std::string firstName = UI.getFirstName();
		std::string surname = UI.getSurname();
		uint64_t personalId = UI.getPersonalId();
		Passenger passenger(firstName, surname, personalId);
		result = file.registerPassanger(passenger);
	}

	return result;
}

bool FlightManager::checkIn() {
	std::string firstName = UI.getFirstName();
	std::string surname = UI.getSurname();
	uint64_t personalId = UI.getPersonalId();

	std::unique_ptr<Flight> flight = nullptr;
	bool repeat = false;
	do {
		uint32_t flightId = UI.getFlightId();

		flight = scheduleFile.searchFlight(flightId);

		if(!flight) {
			repeat = UI.getRepeat();
		}
	} while(repeat);

	bool result = false;
	if(flight) {
		PassengerListFile file(flight->getId());
		//Handle case if booking not available
		Passenger passenger(firstName, surname, personalId);
		result = file.setCheckedIn(passenger);
	}

	return result;
}

bool FlightManager::searchByAirports() {
	bool repeat = false;
	bool rc = false;
	do {
		std::string depatrureCity = UI.getDepartureCity();
		std::string arrivalCity = UI.getArrivalCity();

		std::vector<Flight> flights = scheduleFile.searchFlight(depatrureCity, arrivalCity);

		if(!flights.empty()) {
			UI.display(FlightHeader);
			for(auto flight : flights) {
				std::string str = ScheduleStrFormat::formatRecordUI(flight);
				UI.display(str);
			}
			rc = true;
		} else {
			repeat = UI.getRepeat();
		}
	} while(repeat);

	return rc;
}

bool FlightManager::registerNew() {
	uint32_t flightNo = getGreatestFlightNo() + 1;

	std::string company = UI.getCompany();
	std::string departureCity = UI.getDepartureCity();
	std::string arrivalCity = UI.getArrivalCity();
	DateTime date = UI.getDateTime();

	Flight flight(flightNo, company, date, departureCity, arrivalCity, 300);

	bool result = scheduleFile.registerFlight(flight);
	return result;
}

bool FlightManager::deleteFlight() {
	std::unique_ptr<Flight> flight = nullptr;
	bool repeat = false;
	do {
		uint32_t flightId = UI.getFlightId();

		flight = scheduleFile.searchFlight(flightId);

		if(!flight) {
			repeat = UI.getRepeat();
		}
	} while(repeat);

	bool result = false;
	if(flight) {
		result = scheduleFile.deleteRecord(*flight);
	}
	return result;
}

void FlightManager::chooseAction(uint8_t mainChoice) {
	bool result = false;
	switch(mainChoice) {
	case BOOK:
		result = book();
		break;
	case CHECK_IN:
		result = checkIn();
		break;
	case SEARCH:
		result = searchByAirports();
		break;
	case SHOW_SCHEDULE:
		result = displayAllRecords();
		break;
	case REGISTER:
		result = registerNew();
		break;
	case DELETE:
		result = deleteFlight();
		break;
	case EXIT:
		break;
	default:
		assert(0);
	}
	UI.displayResult(result);
	UI.display("\n\nPress enter in order to continue");
}

