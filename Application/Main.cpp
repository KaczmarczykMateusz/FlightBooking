/*
 * Initial Idea of the project:
 *     Construct Flight management system letting user to add new(admin lvl),
 *     book, check flights, see their schedule and search for flies  (also with interchanges).
 *     Records will be stored in .dat files distinctive to passanger class and flight schedule class.
 *     It will be possible to display schedule for specific airport on specific date.
 *
 *     There will be module of project or separate project to generate random records in order
 *     to test algorithms efficiency etc.
 *
 *     @Notes: Program builds with Gcc compiler with c++ dialect selected to C++14 (-std=c++14)
 *
 */
#include "Common/DateTime.hpp"
#include "FlightManagement/FlightManager.hpp"
#include "UserInterface.hpp"

#include <iostream>
#include <string>
#include <cstdint>
//using std::__cxx11::string; //TODO: check wheteher to enablein windows

int main() {
	FlightManager flightCent;
	uint8_t index = 0;
	while(index != 7) {
		index = flightCent.MainMenu();
		flightCent.ChooseAction(index);
		flightCent.GetUI().Display("\nPress enter in order to continue");
		if(7 != index) {
			std::string str;
			std::getline(std::cin, str);
		}
	}
}
