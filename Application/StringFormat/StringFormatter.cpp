/*
 * StringFormatter.cpp
 *
 *  Created on: 9 Nov 2020
 *      Author: Mateusz
 */

#include "../FlightManagement/Flight.hpp"
#include "../Common/Date.hpp"
#include "../Common/Time.hpp"
#include "../Common/Common.hpp"
#include "StringFormatter.hpp"

#include <iomanip>
#include <sstream>

std::string StringFormatter::formatDate(const Date & date) {
	std::ostringstream outStream;
	outStream << std::setw(2) << std::setfill('0') << static_cast<int>(date.getDay())
			<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getMonth())
			<< static_cast<int>(date.getYear() % 100);
	return outStream.str();
}

std::string StringFormatter::formatTime(const Time & time) {
	std::ostringstream outStream;
	outStream << std::setw(2) << std::setfill('0') << static_cast<int>(time.getHour())
			<< std::setw(2) << std::setfill('0') << static_cast<int>(time.getMinute());
	return outStream.str();
}

std::string StringFormatter::formatDateUI(const Date& date) {
	std::ostringstream dateStream;
	dateStream << std::setw(2) << std::setfill('0') << static_cast<int>(date.getDay()) << "/"
	<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getMonth()) << "/"
	<< static_cast<int>(date.getYear()) << "   ";
	return dateStream.str();
}

std::string StringFormatter::formatTimeUI(const Time & time) {
	std::ostringstream dateStream;
	dateStream << std::setw(2) << std::setfill('0') << static_cast<int>(time.getHour()) << ":"
	<< std::setw(2) << std::setfill('0') << static_cast<int>(time.getMinute());
	return dateStream.str();
}


std::string StringFormatter::getSubStr(const std::string & str, size_t offset, size_t length) {
	std::string retStr("");
	if(  (offset + length) < str.length()) {
		retStr = str.substr(offset, length);
	}
	return retStr;
}
