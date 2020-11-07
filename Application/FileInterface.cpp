/*
 * FileInterface.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "FileInterface.hpp"

#include <cassert>
#include <iostream>


bool FileInterface::GetRecord(std::string &dst, uint16_t recordNumber) {
	bool rc = true;
	openToRead();
	dst.resize(RECORD_LENGTH, '\0');
	flights.seekg(  RECORD_OFFSET * (recordNumber - 1)  );
	flights.read(&dst[0], RECORD_LENGTH);
	if(flights.eof()) {
		rc = false;
	}
	closeFile();
	return rc;
}

uint32_t FileInterface::SearchGreatestNo() {
	openToRead();
	uint32_t greatest = 0;
	uint32_t i = 0;
	while(!flights.eof()) {
		flights.seekg(RECORD_OFFSET*i);
		i++;
		std::string output(NUMBER_LENGTH, '\0');
		flights.read(&output[0], NUMBER_LENGTH);
		if(!flights.eof()) {
			try {
				if(greatest < std::stoul(output)) {
					greatest = std::stoul(output);
				}
			}
			catch(...) {
				greatest = 0;
				assert(false);
			}
		}
	}

	closeFile();
	return greatest;
}

bool FileInterface::SearchDetail(std::string & dst, uint32_t offset, uint16_t length) {
	bool rc = false;
	openToRead();
	flights.seekg(offset);
	std::string str(length, SEPARATOR);
	flights.read(&str[0], length);
	if(!flights.eof()) {
		if(str.length() > length)  {
			rc = false;
		} else {
			StringUtilities::rtrim(str);
			dst = str;
		}
		rc = true;
	}
	closeFile();
	return rc;
}

std::vector<Flight> FileInterface::SearchFlight(std::string departureAirport, std::string arrivalAirport) {
	std::vector<Flight> retVal;
	std::string output(DEPARTURE_AIRPORT_LENGTH, '\0');
	uint32_t recordOffset = 0;
	while(SearchDetail(output, DEPARTURE_AIRPORT_OFFSET + recordOffset, DEPARTURE_AIRPORT_LENGTH)) {
		if(output == departureAirport) {
			output.resize(ARRIVAL_AIRPORT_LENGTH, '\0');
			if(SearchDetail(output, ARRIVAL_AIRPORT_OFFSET + recordOffset, ARRIVAL_AIRPORT_LENGTH)) {
				if(output == arrivalAirport) {
					output.clear();
					output.resize(NUMBER_LENGTH, '\0');
					SearchDetail(output,  NUMBER_OFFSET + recordOffset, NUMBER_LENGTH);
					output.resize(RECORD_LENGTH, '\0');
					GetRecord(output, std::stoul(output));
					retVal.emplace_back(Flight(output));
				}
			}
		}
		output.clear();
		output.resize(DEPARTURE_AIRPORT_LENGTH, '\0');
		recordOffset += RECORD_OFFSET; //TODO: do we need it
	}
	return std::move(retVal);
}

void FileInterface::WriteFlights(const std::string input, uint8_t length) {
	openToWrite();
	std::string text(length, '\0');
	text.replace(0, length, input);
	flights.write(  text.c_str(), length  );	//.c_str() too get C like NULL TERMINED string
	closeFile();
}
