/*
 * UserInterface.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: mateusz
 */

#include "UserInterface.hpp"

#include <cstring>  ///TODO: get rid of together with func using it
#include <iostream>
#include <stdarg.h>  // For va_start, etc.
#include <cassert>


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

std::string UserInterface::GetDate() {
	std::string input(DEPARTURE_DATE_LENGTH + 2, '\0');
	const std::string date[4] = {"DAY", "MONTH", "YEAR", "SEPARATOR"};
	const uint16_t minDate[3] = {1, 1, 2019};
	const uint16_t maxDate[3] = {31, 12, 2050};
	const std::string delimeter(1, '/');

	std::string rc;
	do {
		rc = "";
		std::cout << "Enter date (dd/mm/yyyy) :" << std::endl;
		std::getline(std::cin, input);

		size_t pos = 0;
		for(uint8_t i = 0; i < 3; i++) {
			pos = input.find(delimeter);

			try {
				if(		(std::string::npos == pos)
						&& (2 != i)  ) {
					i = 3;
					throw std::invalid_argument("User; wrong separator");
				}
				std::string tmp(2, '\0');
				tmp = input.substr(0, pos);
				input.erase(0, pos + delimeter.length());
				if(	(minDate[i] > std::stoul(tmp))
						|| (maxDate[i] < std::stoul(tmp)) ) {
					throw std::invalid_argument("User; out of range");
				} else {
					if(tmp.length() > ((DEPARTURE_DATE_LENGTH)/3)) {
						tmp.erase(0, ((DEPARTURE_DATE_LENGTH)/3));
					}
					rc.append(tmp);
				}
			} catch(std::invalid_argument & arg) {
				std::cout << "\n\n\n\n\n\n\n\nException caught by: " << arg.what()  << ".\n" << "You entered WRONG "  << date[i] << "!\n\n";
				break;
			} catch(std::out_of_range & arg) {
				std::cout << "\n\n\n\n\n\n\n\nException caught by: " << arg.what()  << ".\n" << "You entered WRONG "  << date[i] << "!\n\n";
				break;
			}
		}
	} while(6 != rc.size());
	if(6 != rc.size()) {
		throw "Wrong data size caused by program bug (not user)";
	}
	return rc;
}

//Ask user to enter detail and save this detail into dst string
void UserInterface::RegisterRecord(std::string & dst, std::string output, uint32_t offset, uint32_t length) {
	while(1) {
		//output.insert(0, newLineStr);
		Display("%s%s", newLineStr.c_str(), output.c_str());
		std::string input(length, '\0');
		getline(std::cin, input);
		if(length < strlen(input.c_str())) {
			Display("Please enter name not longer than %d", (uint32_t)length-1 );
			continue;
		} else {
			//We need to insert separator because getline adds null termination sign
			input.insert(input.length(), length-input.length(), SEPARATOR);
			try {
				dst.replace(offset, strlen(input.c_str()), input);
			}
			catch(...) {
				Display("dst.size: %d\toffset: %d\tlength: %d", dst.size(), offset, length);
				assert(0);// TODO: consider some action
			}
			break;
		}
	}
}
