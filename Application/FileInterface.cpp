/*
 * FileInterface.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: mateusz
 */

#include "FileInterface.hpp"

#include <iostream>
#include <vector>

bool FileInterface::GetRecord(std::string &dst, uint16_t recordNumber) {
	bool rc = true;
	openToRead();
	flights.seekg(RECORD_OFFSET*(recordNumber - 1));
	flights.read(&dst[0], RECORD_LENGTH);
	if(flights.eof()) {
		rc = false;
	}
	closeFile();
	dst.insert(DEPARTURE_DATE_OFFSET + 2, "/");
	dst.insert(DEPARTURE_DATE_OFFSET + 5, "/");
	dst.insert(DEPARTURE_DATE_OFFSET + 6, "20");
	dst.insert(DEPARTURE_TIME_OFFSET + 4, " ");
	dst.insert(DEPARTURE_TIME_OFFSET + 7, ":");
	return rc;
}

std::string FileInterface::search(SearchBy key, const std::string) {
	std::string str(RECORD_LENGTH, '\0');

	return str;
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
				std::cout << "FAIL SEARCHING FOR NUMBER " << output << std::endl;
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
	//str.replace(0, dst.size(), dst);
	flights.read(&str[0], length);
	if(!flights.eof()) {
		if(str.length() > length)  {
			rc = false;
		} else {
			UI.rtrim(str);
			dst = str;
		}
		rc = true;
	}
	closeFile();
	return rc;
}

void FileInterface::SearchFlight() {
	std::string depatrureCity(DEPARTURE_AIRPORT_LENGTH, SEPARATOR);
	std::string arrivalCity(ARRIVAL_AIRPORT_LENGTH, SEPARATOR);

//	string date = UI.GetDate();
	depatrureCity = UI.GetDepartureCity();
	UI.rtrim(depatrureCity);
	UI.RegisterRecord(arrivalCity, "Insert arrival airport name:\n\n", 0, ARRIVAL_AIRPORT_LENGTH);
	UI.rtrim(arrivalCity);

	std::vector<std::string> retVal;
	std::string output(DEPARTURE_AIRPORT_LENGTH, '\0');
	uint32_t recordOffset = 0;
	while(SearchDetail(output, DEPARTURE_AIRPORT_OFFSET + recordOffset, DEPARTURE_AIRPORT_LENGTH)) {
		if(output == depatrureCity) {\
			output.resize(ARRIVAL_AIRPORT_LENGTH, '\0');
			if(SearchDetail(output, ARRIVAL_AIRPORT_OFFSET + recordOffset, ARRIVAL_AIRPORT_LENGTH)) {
				if(output == arrivalCity) {
					output.clear();
					output.resize(NUMBER_LENGTH, '\0');
				//	SearchDetail(output, recordOffset, RECORD_LENGTH);


					SearchDetail(output,  NUMBER_OFFSET + recordOffset, NUMBER_LENGTH);
					output.resize(RECORD_LENGTH, '\0');
					GetRecord(output, std::stoul(output));
				//	output.resize(RECORD_LENGTH, '\0');


					retVal.push_back(output);
					std::cout << output;
				}
			}
		}
		output.clear();
		output.resize(DEPARTURE_AIRPORT_LENGTH, '\0');
		recordOffset += RECORD_OFFSET; //TODO: do we need it
	}
	if(retVal.empty()) {
		std::cout << "NOT found: " << depatrureCity << ", output: " <<  output << std::endl;
	}
}

void FileInterface::writeFlights(const std::string input, uint8_t length) {
	openToWrite();
	std::string text(length, '\0');
	text.replace(0, length, input);
	flights.write(  text.c_str(), length  );	//.c_str() too get C like NULL TERMINED string
	closeFile();
}
