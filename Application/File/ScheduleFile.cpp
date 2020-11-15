/*
 * ScheduleFile.cpp
 *
 *  Created on: 07 Nov 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "ScheduleFile.hpp"
#include "../StringFormat/ScheduleStrFormat.hpp"

#include <cassert>
#include <iostream>

ScheduleFile::ScheduleFile() :
	File("DB/schedule.dat")
{  }

bool ScheduleFile::getRecord(std::string &dst, uint16_t recordNumber) {
	dst.resize(ScheduleStrFormat::RECORD_LENGTH, '\0');
	uint32_t offset = ScheduleStrFormat::RECORD_OFFSET * (recordNumber - 1);
	dst = File::read(ScheduleStrFormat::RECORD_LENGTH, offset);
	return !dst.empty();
}

uint32_t ScheduleFile::searchGreatestNo() {
	uint32_t greatest = 0;
	uint32_t i = 0;
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
		output = File::read(Config::FLIGHT_ID_LENGTH, ScheduleStrFormat::RECORD_OFFSET * ++i);
	}

	return greatest;
}

std::vector<Flight> ScheduleFile::searchFlight(std::string departureAirport, std::string arrivalAirport) {
	std::vector<Flight> retVal;
	std::string output;
	uint32_t recordOffset = 0;
	uint16_t i = 1;
	do {
		output = File::read(Config::AIRPORT_LENGTH, ScheduleStrFormat::DEPARTURE_AIRPORT_OFFSET + recordOffset);
		StringUtilities::rtrim(output);
		if(output == departureAirport) {
			output = File::read(Config::AIRPORT_LENGTH, ScheduleStrFormat::ARRIVAL_AIRPORT_OFFSET + recordOffset);
			StringUtilities::rtrim(output);
			if(!output.empty()) {
				if(output == arrivalAirport) {
					getRecord(output, i);
					retVal.emplace_back(Flight(output));
				}
			}
		}
		recordOffset += ScheduleStrFormat::RECORD_OFFSET;
		++i;
	} while(!output.empty());
	return std::move(retVal);
}

Flight ScheduleFile::searchFlight(uint32_t flightId) {
	std::string record;
	uint32_t currentRecordId = 0;
	uint32_t recordOffset = 0;
	do {
		record = File::read(Config::FLIGHT_ID_LENGTH, ScheduleStrFormat::NUMBER_OFFSET + recordOffset);
		if(record.empty()) {
			break;
		}
		StringUtilities::rtrim(record);
		try {
			currentRecordId = std::stol(record);
		}
		catch(...) {
		};
		recordOffset += ScheduleStrFormat::RECORD_OFFSET;
	} while(currentRecordId != flightId);

	if(currentRecordId == flightId) {
		record = File::read(ScheduleStrFormat::RECORD_LENGTH, recordOffset - ScheduleStrFormat::RECORD_OFFSET);
		return Flight(record);
	} else {
		return Flight("");
	}
}

void ScheduleFile::registerFlight(const Flight & flight) {
	std::string record = ScheduleStrFormat::formatRecord(flight);
	File::write(record);
}

bool ScheduleFile::deleteRecord(const Flight & flight) {
	bool rc = false;
	std::string deleteFlightNo = std::to_string(flight.getId());

	std::string checkRecord;
	uint32_t recordOffset = 0;
	do {
		checkRecord = File::read(Config::FLIGHT_ID_LENGTH, ScheduleStrFormat::NUMBER_OFFSET + recordOffset);
		StringUtilities::rtrim(checkRecord);
		if(deleteFlightNo == checkRecord) {
			rc = File::erase(recordOffset, ScheduleStrFormat::RECORD_OFFSET);
			break;
		}
		recordOffset += ScheduleStrFormat::RECORD_OFFSET;
	} while(!checkRecord.empty());
	return rc;
}
