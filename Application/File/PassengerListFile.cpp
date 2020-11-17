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

bool PassengerListFile::registerPassanger(const Passenger & passenger) {
	bool rc = false;
	std::string record = PassengerListStrFormat::formatRecord(passenger);
	if(!record.empty()) {
		rc = File::write(record);
	}
	return rc;
}

//TODO: Check on the same way as deleting record in schedule file
bool PassengerListFile::setCheckedIn(Passenger & passenger) {
	bool rc = false;
	std::string output;
	uint16_t offset = 0;
	uint16_t nextRecordOffset = 0;
	do {
		offset += nextRecordOffset;
		nextRecordOffset = PassengerListStrFormat::RECORD_OFFSET;

		output = File::read(Config::SURNAME_LENGTH, PassengerListStrFormat::SURNAME_OFFSET + offset);
		StringUtilities::rtrim(output);
		if(passenger.getSurname() != output) {
			continue;
		}

		output = File::read(Config::FIRST_NAME_LENGTH, PassengerListStrFormat::FIRST_NAME_OFFSET + offset);
		StringUtilities::rtrim(output);
		if(passenger.getFirstName() != output) {
			continue;
		}

		output = File::read(Config::PERSONAL_ID_LENGTH, PassengerListStrFormat::PERSONAL_ID_OFFSET + offset);
		StringUtilities::rtrim(output);
		uint64_t personalId = std::stoll(output);
		if(passenger.getPersonalId() == personalId) {
			std::string toWrite("1");
			File::write(toWrite, offset + PassengerListStrFormat::CHECKED_IN_OFFSET);
			break;
		}
	} while(!output.empty());

	return rc;  //TODO: modify return value checking whether operation succeed
}
