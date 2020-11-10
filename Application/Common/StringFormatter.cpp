/*
 * StringFormatter.cpp
 *
 *  Created on: 9 lis 2020
 *      Author: Mateusz
 */

#include "DateTime.hpp"
#include "../FlightManagement/Flight.hpp"
#include "../Common/Common.hpp"
#include "StringFormatter.hpp"

#include <iomanip>
#include <sstream>

std::string StringFormatter::formatRecord(const Flight & flight) {
	std::string dst(RECORD_LENGTH, ' ');

	RegisterRecordLow(dst, std::to_string(flight.getNo()), NUMBER_OFFSET, NUMBER_LENGTH);
	RegisterRecordLow(dst, flight.getCompany(), COMPANY_NAME_OFFSET, COMPANY_NAME_LENGTH);
	RegisterRecordLow(dst, flight.getDeparture(), DEPARTURE_AIRPORT_OFFSET, DEPARTURE_AIRPORT_LENGTH);
	RegisterRecordLow(dst, flight.getArrival(), ARRIVAL_AIRPORT_OFFSET, ARRIVAL_AIRPORT_LENGTH);
	std::string dateStr = formatDateTime(flight.getDateTime());
	RegisterRecordLow(dst, dateStr, DEPARTURE_DATE_OFFSET, DEPARTURE_DATE_LENGTH + DEPARTURE_TIME_LENGTH);
	RegisterRecordLow(dst, "\n", NEW_LINE_OFFSET, NEW_LINE_LENGTH);

	return dst;
}

std::string StringFormatter::formatDateTime(const DateTime & date) {
	std::ostringstream dateStream;
	dateStream << std::setw(2) << std::setfill('0') << static_cast<int>(date.getDate().getDay())
			<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getDate().getMonth())
			<< static_cast<int>(date.getDate().getYear() % 100)
			<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getTime().getHour())
			<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getTime().getMinute());
	return dateStream.str();
}

std::string StringFormatter::formatRecordUI(const Flight & flight) {
	std::string out(RECORD_LENGTH, ' ');

	out << std::setw(4) << std::setfill('0') <<  flight.getNo() << "  "
			<< flight.getDeparture() << " " << flight.getArrival() << " "  << flight.getCompany() << " "
			<< formatDateTimeUI(flight.getDateTime()) << "\n";

	return out;
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
