/*
 * StringFormatter.cpp
 *
 *  Created on: 9 Nov 2020
 *      Author: Mateusz
 */

#include "../Common/DateTime.hpp"
#include "../FlightManagement/Flight.hpp"
#include "../Common/Common.hpp"
#include "StringFormatter.hpp"

#include <iomanip>
#include <sstream>

std::string StringFormatter::formatDateTime(const DateTime & date) {
	std::ostringstream outStream;
	outStream << std::setw(2) << std::setfill('0') << static_cast<int>(date.getDate().getDay())
			<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getDate().getMonth())
			<< static_cast<int>(date.getDate().getYear() % 100)
			<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getTime().getHour())
			<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getTime().getMinute());
	return outStream.str();
}

std::string StringFormatter::formatDateTimeUI(const DateTime & dateTime) {
	std::ostringstream dateStream;
	dateStream << std::setw(2) << std::setfill('0') << static_cast<int>(dateTime.getDate().getDay()) << "/"
	<< std::setw(2) << std::setfill('0') << static_cast<int>(dateTime.getDate().getMonth()) << "/"
	<< static_cast<int>(dateTime.getDate().getYear()) << "   "
	<< std::setw(2) << std::setfill('0') << static_cast<int>(dateTime.getTime().getHour()) << ":"
	<< std::setw(2) << std::setfill('0') << static_cast<int>(dateTime.getTime().getMinute());
	return dateStream.str();
}

std::string StringFormatter::getSubStr(const std::string & str, size_t offset, size_t length) {
	std::string retStr("");
	if(  (offset + length) < str.length()) {
		retStr = str.substr(offset, length);
	}
	return retStr;
}
