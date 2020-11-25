/*
 * ScheduleFile.cpp
 *
 *  Created on: 07 Nov 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "ScheduleFile.hpp"
#include "../StringFormat/ScheduleStrFormat.hpp"

#include <cassert>

ScheduleFile::ScheduleFile() :
	File("DB/schedule.dat")
{  }

bool ScheduleFile::getRecord(std::string &dst, uint16_t recordNumber) {
	dst.resize(ScheduleStrFormat::RECORD_LENGTH, '\0');
	uint32_t offset = ScheduleStrFormat::RECORD_OFFSET * (recordNumber - 1);
	dst = File::read(ScheduleStrFormat::RECORD_LENGTH, offset);
	return !dst.empty();
}

uint32_t ScheduleFile::getHightstId() {
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

std::vector<Flight> ScheduleFile::searchFlight(const Date & date) {
	std::string output;
	uint16_t i = 1;
	std::vector<uint32_t> foundIndexes;
	std::string targetDateString = ScheduleStrFormat::formatDate(date);
	openToRead();
	uint32_t skipBefore = ScheduleStrFormat::DEPARTURE_DATE_OFFSET;
	do {
		output = File::readOff(Config::DATE_LENGTH, skipBefore);
		skipBefore = ScheduleStrFormat::RECORD_OFFSET - Config::DATE_LENGTH;

		StringUtilities::rtrim(output);
		if(targetDateString == output) {
			foundIndexes.push_back(i);
		}
		++i;
	} while(!output.empty());
	close();

	std::vector<Flight> retVal;
	for(auto index : foundIndexes) {
		getRecord(output, index);
		retVal.emplace_back(Flight(output));
	}
	return std::move(retVal);
}

std::vector<Flight> ScheduleFile::searchFlight(std::string departureAirport, std::string arrivalAirport) {
	std::string output;
	uint16_t i = 1;
	std::vector<uint32_t> foundIndexes;
	uint32_t skipBefore = ScheduleStrFormat::DEPARTURE_AIRPORT_OFFSET;
	openToRead();
	do {
		output = File::readOff(Config::AIRPORT_LENGTH, skipBefore);
		StringUtilities::rtrim(output);
		if(output == departureAirport) {
			skipBefore = 0;
			output = File::readOff(Config::AIRPORT_LENGTH, skipBefore);
			skipBefore = ScheduleStrFormat::RECORD_OFFSET - ScheduleStrFormat::ARRIVAL_AIRPORT_OFFSET + 1;
			StringUtilities::rtrim(output);
			if(!output.empty()) {
				if(output == arrivalAirport) {
					foundIndexes.push_back(i);
				}
			}
		} else {
			skipBefore = ScheduleStrFormat::RECORD_OFFSET - (Config::AIRPORT_LENGTH);
		}
		++i;
	} while(!output.empty());
	close();

	std::vector<Flight> retVal;
	for(auto index : foundIndexes) {
		getRecord(output, index);
		retVal.emplace_back(Flight(output));
	}
	return std::move(retVal);
}

std::unique_ptr<Flight> ScheduleFile::searchFlight(uint32_t flightId) {
	std::string record;
	uint32_t currentRecordId = 0;
	uint32_t skipBefore = ScheduleStrFormat::ID_OFFSET;
	openToRead();
	do {
		record = File::readOff(Config::FLIGHT_ID_LENGTH, skipBefore);
		if(record.empty()) {
			break;
		}
		StringUtilities::rtrim(record);
		try {
			currentRecordId = std::stol(record);
		}
		catch(...) {
			currentRecordId = 0;
		};
		skipBefore = ScheduleStrFormat::RECORD_OFFSET - (Config::FLIGHT_ID_LENGTH);
	} while(currentRecordId != flightId);
	close();

	if(currentRecordId == flightId) {
		getRecord(record, currentRecordId);
		return std::make_unique<Flight>(record);
	} else {
		return nullptr;
	}
}

bool ScheduleFile::registerFlight(const Flight & flight) {
	bool rc = false;
	std::string record = ScheduleStrFormat::formatRecord(flight);
	if(!record.empty()) {
		rc = File::write(record);
	}
	return rc;
}

bool ScheduleFile::deleteRecord(const Flight & flight) {
	bool rc = false;
	std::string toRemove = ScheduleStrFormat::formatRecord(flight);
	rc = File::eraseRecord(toRemove, ScheduleStrFormat::RECORD_LENGTH);
	return rc;
}
