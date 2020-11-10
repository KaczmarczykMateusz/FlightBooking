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

static const std::string departureCityReq = "Insert departure airport name:\n\n";
static const std::string arrivalCityReq = "Insert arrival airport name:\n\n";

void UserInterface::Display(const std::string fmt, ...) {
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

Date UserInterface::GetDate() {
	uint16_t year = 0;
	uint8_t month = 0, day = 0;

	std::string input(DEPARTURE_DATE_LENGTH + 2, '\0');
	const std::string date[4] = {"DAY", "MONTH", "YEAR", "SEPARATOR"};
	const uint16_t minDate[3] = {1, 1, 2019};
	const uint16_t maxDate[3] = {31, 12, 2050};
	const std::string delimeter(1, '/');

	do {
		std::cout << "Enter date (dd/mm/yyyy) :" << std::endl;
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

Time UserInterface::GetTime() {
	uint8_t hour = 0, minute = 0;
	const std::string delimeter(":");
	std::string input(DEPARTURE_TIME_LENGTH + 1, '\0');
	do {
		std::cout << "Enter time (hh:mm) :" << std::endl;
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
					minute = static_cast<uint8_t>(num);
				}
			} catch(...) {
				std::cout << "\n\nInvalid number!\n\n";
				break;
			}
		}
	} while(!minute);

	return Time(hour, minute);
}

DateTime UserInterface::GetDateTime() {
	Date date(this->GetDate());
	Time time(this->GetTime());
	return DateTime(date, time);
}

void UserInterface::getLine(std::string & dst, uint32_t length) {
	do {
		getline(std::cin, dst);
		if(!validateLength(dst, length)) {
			continue;
		}
	} while(0);
}

std::string UserInterface::GetCompany() {
	Display("%sInsert company name:\n\n", newLineStr.c_str());
	std::string str;
	getLine(str, COMPANY_NAME_LENGTH);
	rtrim(str);
	return str;
}

std::string UserInterface::GetDepartureCity() {
	Display("%s%s", newLineStr.c_str(), departureCityReq.c_str());
	std::string str;
	getLine(str, DEPARTURE_AIRPORT_LENGTH);
	rtrim(str);
	return str;
}

std::string UserInterface::GetArrivalCity() {
	Display("%s%s", newLineStr.c_str(), arrivalCityReq.c_str());
	std::string str;
	getLine(str, ARRIVAL_AIRPORT_LENGTH);
	rtrim(str);
	return str;
}


bool UserInterface::validateLength(const std::string & str, uint32_t length) {
	bool rc = (length > strlen(str.c_str()));
	if(!rc) {
		Display("Please enter name not longer than %d", (uint32_t)length-1 );
	}
	return rc;
}
