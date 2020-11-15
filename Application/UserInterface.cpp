/*
 * UserInterface.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: mateusz
 */

#include "UserInterface.hpp"
#include "Common/DateTime.hpp"

#include <cstring>  ///TODO: get rid of together with func using it
#include <iostream>
#include <stdarg.h>  // For va_start, etc.
#include <cassert>

static const std::string departureCityReq = "Insert departure airport name:\n";
static const std::string arrivalCityReq = "Insert arrival airport name:\n";
static const std::string firstNameReq = "Insert first name:\n";
static const std::string surnameReq = "Insert surname:\n";
static const std::string personalIdReq = "Insert ID card number:\n";
static const std::string flightIdReq = "Insert number of flight:\n";
static const std::string notFound = "\n\nNot found, would you like to repeat "
										"search (y/n)\n";

void UserInterface::display(const std::string fmt, ...) {
	va_list ap;
	std::string str;
	int32_t size = fmt.length() * 2 + 20;
	while(1) {
		str.resize(size);
		va_start(ap, fmt);
		int32_t n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
		va_end(ap);
		if(-1 < n && n < size) { //Success
			str.resize(n);
			break;
		} else if(n == size) { //Add space for Null terminations sign
			size += 1;
		} else if(-1 < n) {	//Reserve more space
			size += n * 2;
		} else {
			assert(0); //XXXwe should never rnd up here
			throw std::runtime_error("Error in string processing");
		}
	}
	std::cout << str;
}

void UserInterface::displayResult(bool result) {
	if(result) {
		display("\n\nSuccess.");
	} else {
		display("\n\nFail, please try again.");
	}

}
Date UserInterface::getDate() {
	uint16_t year = 0;
	uint8_t month = 0, day = 0;

	std::string input(Config::DATE_LENGTH + 2, '\0');
	const std::string date[4] = {"DAY", "MONTH", "YEAR", "SEPARATOR"};
	const uint16_t minDate[3] = {1, 1, 2019};
	const uint16_t maxDate[3] = {31, 12, 2050};
	const std::string delimeter(1, '/');

	do {
		std::cout << "\n\nEnter date (dd/mm/yyyy) :" << std::endl;
		std::getline(std::cin, input);

		for(uint8_t i = 0; i < 3; i++) {
			size_t pos = input.find(delimeter);

			if(  (std::string::npos == pos) && (2 != i)  ) {
				i = 3;
				std::cout << "\n\nEnter correct separator (\"/\") !\n\n";
				break;
			}
			try {
				std::string tmp = input.substr(0, pos);
				input.erase(0, pos + delimeter.length());
				uint32_t num = std::stoul(tmp);
				if(  (minDate[i] > num) || (maxDate[i] < num)  ) {
					std::cout << "\n\n"  << date[i] << " out of range !\n\n";
					break;
				} else {
					switch(i) {
					case 0:
						day = static_cast<uint8_t>(num);
						break;
					case 1:
						month = static_cast<uint8_t>(num);
						break;
					case 2:
					default:
						year = static_cast<uint16_t>(num);
					}
				}
			} catch(...) {
				std::cout << "\n\nInvalid number!\n\n";
				break;
			}
		}
	} while(!year);

	return Date(year, month, day);
}

Time UserInterface::getTime() {
	uint8_t hour = 0;
	int16_t minute = -1;
	const std::string delimeter(":");
	std::string input(Config::TIME_LENGTH + 1, '\0');
	do {
		std::cout << "\n\nEnter time (hh:mm) :" << std::endl;
		std::getline(std::cin, input);

		for(uint8_t i = 0; i < 2; i++) {
			size_t pos = input.find(delimeter);

			if(  (std::string::npos == pos) && (1 != i)  ) {
				i = 2;
				std::cout << "\n\nEnter correct separator (\":\") !\n\n";
				break;
			}
			try {
				std::string tmp = input.substr(0, pos);
				input.erase(0, pos + delimeter.length());
				uint32_t num = std::stoul(tmp);
				if(!i) {
					if(24 < num) {
						std::cout << "\n\nHour out of range !\n\n";
						break;
					}
					hour = static_cast<uint8_t>(num);
				} else {
					if(60 < num) {
						std::cout << "\n\nMinute out of range !\n\n";
						break;
					}
					minute = static_cast<int16_t>(num);
				}
			} catch(...) {
				std::cout << "\n\nInvalid number!\n\n";
				break;
			}
		}
	} while(0 > minute);

	return Time(hour, minute);
}

DateTime UserInterface::getDateTime() {
	Date date(this->getDate());
	Time time(this->getTime());
	return DateTime(date, time);
}

std::string UserInterface::getLine(uint32_t length) {
	std::string str("");
	do {
		str = "";
		getline(std::cin, str);
	} while(!validateLength(str, length));

	rtrim(str);
	return str;
}

uint64_t UserInterface::getNumber(uint32_t length) {
	uint64_t rc = 0;
	do {
		std::string str = getLine(length);
		try {
			rc = std::stoull(str);
		}
		catch(...) {
			rc = 0;
		}
	} while(!rc);
	return rc;
}

std::string UserInterface::getCompany() {
	display("\n\nInsert company name:\n");
	std::string str = getLine(Config::COMPANY_NAME_LENGTH);
	return str;
}

std::string UserInterface::getDepartureCity() {
	display("\n\n%s", departureCityReq.c_str());
	std::string str = getLine(Config::AIRPORT_LENGTH);
	return str;
}

std::string UserInterface::getArrivalCity() {
	display("\n\n%s", arrivalCityReq.c_str());
	std::string str = getLine(Config::AIRPORT_LENGTH);
	return str;
}

std::string UserInterface::getFirstName() {
	display("\n\n%s", firstNameReq.c_str());
	std::string str = getLine(Config::FIRST_NAME_LENGTH);
	return str;
}

std::string UserInterface::getSurname() {
	display("\n\n%s", surnameReq.c_str());
	std::string str = getLine(Config::SURNAME_LENGTH);
	return str;
}

uint64_t UserInterface::getPersonalId() {
	display("\n\n%s", personalIdReq.c_str());
	return getNumber(Config::PERSONAL_ID_LENGTH);
}

uint32_t UserInterface::getFlightId() {
	display("\n\n%s", flightIdReq.c_str());
	return static_cast<uint32_t>(getNumber(Config::FLIGHT_ID_LENGTH));
}

bool UserInterface::getRepeat() {
	display(notFound);
	std::string str;
	getline(std::cin, str);
	switch(str[0]) {
	case 'y':
		return true;
	case 'n':
	default:
		return false;
	};
}

bool UserInterface::validateLength(const std::string & str, uint32_t length) {
	bool rc = true;
	if(str.empty()) {
		display("Please enter requested input\n", length-1 );
		rc = false;
	} else if(length < strlen(str.c_str())) {
		display("Please enter input not longer than %d\n", length-1 );
		rc = false;
	}
	return rc;
}
