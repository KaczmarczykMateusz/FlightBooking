/*
 * StringFormatter.hpp
 *
 *  Created on: 9 lis 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_COMMON_STRINGFORMATTER_HPP_
#define APPLICATION_COMMON_STRINGFORMATTER_HPP_

#include <string>
#include <cstring>  //strlen //TODO: remove strlen()
#include <cassert>

class StringFormatter {
public:
	StringFormatter() = default;

	static std::string FormatLine(uint32_t flightNo, const std::string & company, const std::string & departureAirport, const std::string & arrivalAirport, const std::string & date);

private:
	//Ask user to enter detail and save this detail into dst string
	static void RegisterRecordLow(std::string & dst, std::string input, uint32_t offset, uint32_t length) {
		//dst.resize(length, ' ');
		do {
			try {
				dst.replace(offset, strlen(input.c_str()), input);
			}
			catch(...) {
				//Display("dst.size: %d\toffset: %d\tlength: %d", dst.size(), offset, length);
				assert(0);// TODO: consider some action
			}
		} while(0);
	}
};

#endif /* APPLICATION_COMMON_STRINGFORMATTER_HPP_ */
