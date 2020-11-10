/*
 * StringFormatter.cpp
 *
 *  Created on: 9 lis 2020
 *      Author: Mateusz
 */

#include "DateTime.hpp"
#include "../Common/Common.hpp"
#include "StringFormatter.hpp"

#include <iomanip>
#include <sstream>

std::string StringFormatter::FormatLine(uint32_t flightNo, const std::string & company, const std::string & departureAirport, const std::string & arrivalAirport, const DateTime & date) {
	std::string dst(RECORD_LENGTH, ' ');

	RegisterRecordLow(dst, std::to_string(flightNo), NUMBER_OFFSET, NUMBER_LENGTH);
	RegisterRecordLow(dst, company, COMPANY_NAME_OFFSET, COMPANY_NAME_LENGTH);
	RegisterRecordLow(dst, departureAirport, DEPARTURE_AIRPORT_OFFSET, DEPARTURE_AIRPORT_LENGTH);
	RegisterRecordLow(dst, arrivalAirport, ARRIVAL_AIRPORT_OFFSET, ARRIVAL_AIRPORT_LENGTH);
	std::string dateStr = FormatDateTime(date);
	RegisterRecordLow(dst, dateStr, DEPARTURE_DATE_OFFSET, DEPARTURE_DATE_LENGTH + DEPARTURE_TIME_LENGTH);
	RegisterRecordLow(dst, "\n", NEW_LINE_OFFSET, NEW_LINE_LENGTH);

	return dst;
}

std::string StringFormatter::FormatDateTime(const DateTime & date) {
	std::ostringstream dateStream;
	dateStream << static_cast<int>(date.getDate().getDay())
			<< static_cast<int>(date.getDate().getMonth())
			<< static_cast<int>(date.getDate().getYear() % 100)
			<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getTime().getHour())
			<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getTime().getMinute());
	return dateStream.str();
}

std::string StringFormatter::FormatDateUI(const DateTime & date) {
	std::ostringstream dateStream;
	dateStream << date.getDate().getDay() << "/"
			<< date.getDate().getMonth() << "/"
			<< date.getDate().getYear();
	return dateStream.str();
}
