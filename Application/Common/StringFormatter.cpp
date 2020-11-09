/*
 * StringFormatter.cpp
 *
 *  Created on: 9 lis 2020
 *      Author: Mateusz
 */

#include "../Common/Common.hpp"
#include "StringFormatter.hpp"


std::string StringFormatter::FormatLine(uint32_t flightNo, const std::string & company, const std::string & departureAirport, const std::string & arrivalAirport, const std::string & date) {
		std::string dst(RECORD_LENGTH, ' ');

		RegisterRecordLow(dst, std::to_string(flightNo), NUMBER_OFFSET, NUMBER_LENGTH);
		RegisterRecordLow(dst, company, COMPANY_NAME_OFFSET, COMPANY_NAME_LENGTH);
		RegisterRecordLow(dst, departureAirport, DEPARTURE_AIRPORT_OFFSET, DEPARTURE_AIRPORT_LENGTH);
		RegisterRecordLow(dst, arrivalAirport, ARRIVAL_AIRPORT_OFFSET, ARRIVAL_AIRPORT_LENGTH);
		RegisterRecordLow(dst, date, DEPARTURE_DATE_OFFSET, DEPARTURE_DATE_LENGTH);
		RegisterRecordLow(dst, "\n", NEW_LINE_OFFSET, NEW_LINE_LENGTH);

		return dst;
	}
