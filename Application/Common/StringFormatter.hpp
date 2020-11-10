/*
 * StringFormatter.hpp
 *
 *  Created on: 9 lis 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_COMMON_STRINGFORMATTER_HPP_
#define APPLICATION_COMMON_STRINGFORMATTER_HPP_

#include <string>
#include <cassert>

class DateTime;
class Flight;

class StringFormatter {
public:
	StringFormatter() = default;

	static std::string formatDateTime(const DateTime & date);
	static std::string formatRecord(const Flight & flight);

	static std::string formatDateTimeUI(const DateTime & dateTime);
	static std::string formatRecordUI(const Flight & flight);

private:
	//Ask user to enter detail and save this detail into dst string
	static void RegisterRecordLow(std::string & dst, std::string input, uint32_t offset, uint32_t length) {
		//dst.resize(length, ' ');
		do {
			try {
				dst.replace(offset, input.length(), input);
			}
			catch(...) {
				//Display("dst.size: %d\toffset: %d\tlength: %d", dst.size(), offset, length);
				assert(0);// TODO: consider some action
			}
		} while(0);
	}

};

#endif /* APPLICATION_COMMON_STRINGFORMATTER_HPP_ */
