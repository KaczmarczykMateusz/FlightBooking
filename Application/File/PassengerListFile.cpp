/*
 * PassengerListFile.cpp
 *
 *  Created on: 07 Nov 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "PassengerListFile.hpp"
#include "../StringFormat/PassengerListStrFormat.hpp"
#include "../FlightManagement/Passenger.h"


#include <cassert>
#include <sstream>

PassengerListFile::PassengerListFile(uint32_t flightNo) :
	File("DB/PassengerLists/EMPTY")
{
	std::ostringstream name;
	name << "DB/PassengerLists/flight_no_" << std::to_string(flightNo) << ".dat";
	File::setName(name.str());
}

bool PassengerListFile::getRecord(std::string &dst, uint16_t recordNumber) {
	dst.resize(PassengerListStrFormat::RECORD_LENGTH, '\0');
	uint32_t offset = PassengerListStrFormat::RECORD_OFFSET * (recordNumber - 1);
	dst = File::read(PassengerListStrFormat::RECORD_LENGTH, offset);
	return !dst.empty();
}

uint32_t PassengerListFile::getNewRecordOffset() {
	uint32_t greatest = 0;
	uint32_t offset = 0;
	std::string output = File::read(Config::FLIGHT_ID_LENGTH, 0);
	while(!output.empty()) {
		try {
			if(greatest < std::stoul(output)) {
				greatest = std::stoul(output);
			}
		}
		catch(...) {
			greatest = 0;
			assert(false);
		}
		offset += output.length();
		output = File::read(Config::FLIGHT_ID_LENGTH, offset);
	}

	return greatest;
}

Passenger PassengerListFile::searchPassanger(std::string name, std::string surname) {
	std::string output;
	uint16_t offset = 0;
	do {
		output = File::read(Config::SURNAME_LENGTH, PassengerListStrFormat::SURNAME_OFFSET + offset);
		if(output == surname) {
			output = File::read(Config::FIRST_NAME_LENGTH, PassengerListStrFormat::FIRST_NAME_OFFSET + offset);
			if(!output.empty()) {
				if(output == name) {
					getRecord(output, offset);
					return Passenger(output);
				}
			}
		}
		offset += output.length();
	} while(!output.empty());
	return Passenger("");
}

void PassengerListFile::registerPassanger(const Passenger & passenger) {
	std::string record = PassengerListStrFormat::formatRecord(passenger);
	File::write(record);
}
