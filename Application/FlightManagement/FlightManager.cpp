/*
 * FlightManager.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: mateusz
 */

#include "FlightManager.hpp"

#include <cassert>
#include <iostream>

uint8_t FlightManager::MainMenu() {
	uint8_t choice = 0;
	do {
		//memcpy(&text[0], " ", 1);	//It's allowed since c++11
		std::string text =
		{ "\n"
		"--------------------------------------------------------\n"
		"***************FLIGHT CENTER POKAHONTAS****************\n"
		"--------------------------------------------------------\n"
		"What would you like to do: (chose with numeric keypad)\n"
		"1 - Book new fligt            2 - Check-in\n"
		"3 - Check your fligt          4 - Check flight schedule\n"
		"5 - Register new flight       6 - Delete flight\n"
		"7 - Exit system\n" };
		UI.Display(text);

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
			text = { "\n\n\n\n\n\nInvalid number, please enter right digit\n\n" };
			std::cout << "\n\n\n Entered digit:   " << choice << std::endl;
			UI.Display(text);
		}
	} while(7 < (choice-'0'));
	return choice;
}

uint32_t FlightManager::GeteGreatestFlightNo(FileInterface & file) {
	return file.SearchGreatestNo();
}

void FlightManager::DisplayAllRecords(FileInterface & file) {
	uint8_t getIndex = 1;
	std::string output(RECORD_LENGTH, '\0');
	while(file.GetRecord(output, getIndex)) {
		getIndex +=1;
		UI.Display(output);
		output.resize(RECORD_OFFSET, '\0');
	}
}

void FlightManager::Book() {
/*		string str(DEPARTURE_AIRPORT_LENGTH ,'\0');
	UI.Display("From where do you want to departure? Enter city name: ");
	getline(cin, str);
	str.empty();
	UI.Display("Where do you want to go? Enter city name: ");
	getline(cin, str);*/
	File.SearchFlight();
	//TODO: continue with booking
}

void FlightManager::RegisterNew() {
	std::string numberStr(NUMBER_LENGTH+1, ' ');
	uint32_t flightNo = GeteGreatestFlightNo(File) + 1;

	std::string company = UI.GetCompany();
	std::string departureCity = UI.GetDepartureCity();
	std::string arrivalCity = UI.GetArrivalCity();
	std::string date = UI.GetDate();

	std::string record = UI.FormatLine(flightNo, company, departureCity, arrivalCity, date);

	File.writeFlights(record, RECORD_LENGTH);
}

void FlightManager::ChooseAction(uint8_t mainChoice) {
	switch(mainChoice) {
	case 1:    //Book new fligt
		Book();
		break;
	case 2:    //Check-in
		assert(0); //TODO: fill case
		break;
	case 3:    //Check your fligt
		assert(0);
		break;
	case 4:    //Check flight schedule
		DisplayAllRecords(File);
		break;
	case 5:    //Register new flight
		RegisterNew();
		break;
	case 6:    //Delete flight
		assert(0); //TODO: fill case
		break;
	case 7:    //Exit program
		break;
	default:
		assert(0);
	}
}

UserInterface & FlightManager::GetUI() {
	return UI;
}
