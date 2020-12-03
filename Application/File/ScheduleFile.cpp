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

uint32_t ScheduleFile::getHightstId() {
	uint32_t greatest = 0;
	std::string output;

	openToRead();
	uint32_t relativeOffset = ScheduleStrFormat::ID_OFFSET;
	output = File::read(Config::FLIGHT_ID_LENGTH, relativeOffset);
	while(!output.empty()) {
		try {
			if(greatest < std::stoul(output)) {
				greatest = std::stoul(output);
			}
		}
		catch(...) {
			greatest = 0;
			assert(false);
			break;
		}
		relativeOffset = ScheduleStrFormat::RECORD_LENGTH - (Config::FLIGHT_ID_LENGTH);
		output = File::read(Config::FLIGHT_ID_LENGTH, relativeOffset);
	}
	close();

	return greatest;
}

std::vector<Flight> ScheduleFile::searchFlight(const Date & date) {
	std::vector<Flight> retVal;
	std::string targetDateString = ScheduleStrFormat::formatDate(date);

	openToRead();
	uint32_t relativeOffset = ScheduleStrFormat::DEPARTURE_DATE_OFFSET;
	std::string output = File::read(Config::DATE_LENGTH, relativeOffset);
	while(!output.empty()) {
		StringUtilities::rtrim(output);
		if(targetDateString == output) {
			relativeOffset = -(ScheduleStrFormat::DEPARTURE_DATE_OFFSET + Config::DATE_LENGTH);
			output = File::read(ScheduleStrFormat::RECORD_LENGTH, relativeOffset);
			retVal.emplace_back(Flight(output));
			relativeOffset = ScheduleStrFormat::DEPARTURE_DATE_OFFSET;
		} else {
			relativeOffset = ScheduleStrFormat::RECORD_LENGTH - Config::DATE_LENGTH;
		}
		output = File::read(Config::DATE_LENGTH, relativeOffset);
	}
	close();

	return std::move(retVal);
}

std::vector<Flight> ScheduleFile::searchFlight(std::string departureAirport, std::string arrivalAirport) {
	std::vector<Flight> retVal;
	StringUtilities::toLower(departureAirport);
	StringUtilities::toLower(arrivalAirport);

	openToRead();
	uint32_t relativeOffset = ScheduleStrFormat::DEPARTURE_AIRPORT_OFFSET;
	std::string output = File::read(Config::AIRPORT_LENGTH, relativeOffset);
	while(!output.empty()) {
		StringUtilities::rtrim(output);
		StringUtilities::toLower(output);
		if(output == departureAirport) {
			relativeOffset = 0;
			output = File::read(Config::AIRPORT_LENGTH, relativeOffset);
			relativeOffset = ScheduleStrFormat::RECORD_LENGTH - ScheduleStrFormat::ARRIVAL_AIRPORT_OFFSET + 1;
			StringUtilities::rtrim(output);
			StringUtilities::toLower(output);
			if(!output.empty()) {
				if(output == arrivalAirport) {
					relativeOffset = -(ScheduleStrFormat::ARRIVAL_AIRPORT_OFFSET + Config::AIRPORT_LENGTH);
					output = File::read(ScheduleStrFormat::RECORD_LENGTH, relativeOffset);
					retVal.emplace_back(Flight(output));
					relativeOffset = ScheduleStrFormat::DEPARTURE_AIRPORT_OFFSET;
				}
			}
		} else {
			relativeOffset = ScheduleStrFormat::RECORD_LENGTH - Config::AIRPORT_LENGTH;
		}
		output = File::read(Config::AIRPORT_LENGTH, relativeOffset);
	}
	close();

	return std::move(retVal);
}

std::unique_ptr<Flight> ScheduleFile::searchFlight(uint32_t flightId) {
	std::string output;
	uint32_t currentRecordId = 0;
	uint32_t relativeOffset = ScheduleStrFormat::ID_OFFSET;
	openToRead();
	output = File::read(Config::FLIGHT_ID_LENGTH, relativeOffset);
	while(!output.empty()) {
		StringUtilities::rtrim(output);
		try {
			currentRecordId = std::stol(output);
		}
		catch(...) {
			currentRecordId = 0;
		};
		if(currentRecordId != flightId) {
			relativeOffset = ScheduleStrFormat::RECORD_LENGTH - (Config::FLIGHT_ID_LENGTH);
		} else {
			relativeOffset = -(ScheduleStrFormat::ID_OFFSET + Config::FLIGHT_ID_LENGTH);
			output = File::read(ScheduleStrFormat::RECORD_LENGTH, relativeOffset);
			break;
		}
		output = File::read(Config::FLIGHT_ID_LENGTH, relativeOffset);
	}
	close();

	if(currentRecordId == flightId) {
		return std::make_unique<Flight>(output);
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
