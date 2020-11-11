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

std::string StringFormatter::formatRecord(const Flight & flight) {
	std::string dst(FlightDef::RECORD_LENGTH, ' ');

	repalaceInString(dst, std::to_string(flight.getNo()), FlightDef::NUMBER_OFFSET);
	repalaceInString(dst, flight.getCompany(), FlightDef::COMPANY_NAME_OFFSET);
	repalaceInString(dst, flight.getDeparture(), FlightDef::DEPARTURE_AIRPORT_OFFSET);
	repalaceInString(dst, flight.getArrival(), FlightDef::ARRIVAL_AIRPORT_OFFSET);
	std::string dateStr = formatDateTime(flight.getDateTime());
	repalaceInString(dst, dateStr, FlightDef::DEPARTURE_DATE_OFFSET);
	repalaceInString(dst, "\n", FlightDef::NEW_LINE_OFFSET);

	return dst;
}

std::string StringFormatter::formatDateTime(const DateTime & date) {
	std::ostringstream outStream;
	outStream << std::setw(2) << std::setfill('0') << static_cast<int>(date.getDate().getDay())
			<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getDate().getMonth())
			<< static_cast<int>(date.getDate().getYear() % 100)
			<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getTime().getHour())
			<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getTime().getMinute());
	return outStream.str();
}

std::string StringFormatter::formatRecordUI(const Flight & flight) {
	std::ostringstream outStream;

	outStream << std::setw(4) << std::setfill('0') <<  flight.getNo() << "  "
			<< flight.getDeparture() << " " << flight.getArrival() << " "  << flight.getCompany() << " "
			<< formatDateTimeUI(flight.getDateTime()) << "\n";

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
