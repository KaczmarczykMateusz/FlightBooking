/*
 * ScheduleFile.cpp
 *
 *  Created on: 07 Nov 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "ScheduleFile.hpp"
#include "../StringFormat/StringFormatter.hpp"

#include <cassert>
#include <iostream>

ScheduleFile::ScheduleFile() :
	File("schedule.dat")
{  }

bool ScheduleFile::getRecord(std::string &dst, uint16_t recordNumber) {
	dst.resize(FlightDef::RECORD_LENGTH, '\0');
	uint32_t offset = FlightDef::RECORD_OFFSET * (recordNumber - 1);
	dst = File::read(FlightDef::RECORD_LENGTH, offset);
	return !dst.empty();
}

uint32_t ScheduleFile::searchGreatestNo() {
	uint32_t greatest = 0;
	uint32_t i = 0;
	std::string output = File::read(Config::NUMBER_LENGTH, 0);
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
		output = File::read(Config::NUMBER_LENGTH, FlightDef::RECORD_OFFSET * ++i);
	}

	return greatest;
}

std::string ScheduleFile::searchDetail(uint32_t offset, uint16_t length) {
	std::string rc = "";
	std::string str = File::read(length, offset);
	if(!str.empty()) {
		if(str.length() <= length)  {
			StringUtilities::rtrim(str);
			rc = str;
		}
	}
	return rc;
}

std::vector<Flight> ScheduleFile::searchFlight(std::string departureAirport, std::string arrivalAirport) {
	std::vector<Flight> retVal;
	std::string output;
	uint32_t recordOffset = 0;
	uint16_t i = 1;
	do {
		output = searchDetail(FlightDef::DEPARTURE_AIRPORT_OFFSET + recordOffset, Config::AIRPORT_LENGTH);
		if(output == departureAirport) {
			output = searchDetail(FlightDef::ARRIVAL_AIRPORT_OFFSET + recordOffset, Config::AIRPORT_LENGTH);
			if(!output.empty()) {
				if(output == arrivalAirport) {
					output = searchDetail(FlightDef::NUMBER_OFFSET + recordOffset, Config::NUMBER_LENGTH);
					getRecord(output, i);
					retVal.emplace_back(Flight(output));
				}
			}
		}
		recordOffset += FlightDef::RECORD_OFFSET;
		++i;
	} while(!output.empty());
	return std::move(retVal);
}

void ScheduleFile::registerFlight(const Flight & flight) {
	std::string record = StringFormatter::formatRecord(flight);
	File::write(record);
}
