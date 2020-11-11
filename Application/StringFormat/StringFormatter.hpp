/*
 * StringFormatter.hpp
 *
 *  Created on: 9 Nov 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_STRINGFORMAT_STRINGFORMATTER_HPP_
#define APPLICATION_STRINGFORMAT_STRINGFORMATTER_HPP_

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
	static void repalaceInString(std::string & dst, std::string input, uint32_t offset) {
		try {
			dst.replace(offset, input.length(), input);
		}
		catch(...) {
			//Display("dst.size: %d\toffset: %d\tlength: %d", dst.size(), offset, length);
			assert(0);// TODO: consider some action
		}
	}
};

#endif /* APPLICATION_COMMON_STRINGFORMATTER_HPP_ */
