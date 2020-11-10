/*
 * FlightFile.cpp
 *
 *  Created on: 07 Nov 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "FlightFile.hpp"
#include "../Common/StringFormatter.hpp"

#include <cassert>
#include <iostream>

FlightFile::FlightFile() :
	File("flights.dat")
{  }

bool FlightFile::getRecord(std::string &dst, uint16_t recordNumber) {
	dst.resize(RECORD_LENGTH, '\0');
	uint32_t offset = RECORD_OFFSET * (recordNumber - 1);
	dst = File::read(RECORD_LENGTH, offset);
	return !dst.empty();
}

uint32_t FlightFile::searchGreatestNo() {
	uint32_t greatest = 0;
	uint32_t i = 0;
	std::string output = File::read(NUMBER_LENGTH, 0);
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
		output = File::read(NUMBER_LENGTH, RECORD_OFFSET * ++i);
	}

	return greatest;
}

std::string FlightFile::searchDetail(uint32_t offset, uint16_t length) {
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

std::vector<Flight> FlightFile::searchFlight(std::string departureAirport, std::string arrivalAirport) {
	std::vector<Flight> retVal;
	std::string output(DEPARTURE_AIRPORT_LENGTH, '\0');
	uint32_t recordOffset = 0;
	do {
		output = searchDetail(DEPARTURE_AIRPORT_OFFSET + recordOffset, DEPARTURE_AIRPORT_LENGTH);
		if(output == departureAirport) {
			output = searchDetail(ARRIVAL_AIRPORT_OFFSET + recordOffset, ARRIVAL_AIRPORT_LENGTH);
			if(!output.empty()) {
				if(output == arrivalAirport) {
					output = searchDetail(NUMBER_OFFSET + recordOffset, NUMBER_LENGTH);
					uint16_t flightIndex = std::stoul(output);
					getRecord(output, flightIndex);
					retVal.emplace_back(Flight(output));
				}
			}
		}
		recordOffset += RECORD_OFFSET;
	} while(!output.empty());
	return std::move(retVal);
}

void FlightFile::registerFlight(const Flight & flight) {
	std::string record = StringFormatter::formatRecord(flight);
	File::write(record);
}
