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

class Date;
class DateTime;
class Flight;

class StringFormatter {
public:
	StringFormatter() = default;

	static std::string formatDate(const Date & date);
	static std::string formatDateTime(const DateTime & dateTime);

	static std::string formatDateTimeUI(const DateTime & dateTime);
protected:
	//Ask user to enter detail and save this detail into dst string
	static bool repalaceInString(std::string & dst, std::string input, uint32_t offset) {
		bool rc = false;
		try {
			dst.replace(offset, input.length(), input);
			rc = true;
		}
		catch(...) {
			rc = false;
			assert(0);
		}
		return rc;
	}
	static std::string getSubStr(const std::string & str, size_t offset, size_t length);
};

#endif /* APPLICATION_COMMON_STRINGFORMATTER_HPP_ */
