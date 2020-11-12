/*
 * ScheduleStrFormat.cpp
 *
 *  Created on: 12 Nov 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "../Common/DateTime.hpp"
#include "../FlightManagement/Flight.hpp"
#include "../Common/Common.hpp"
#include "ScheduleStrFormat.hpp"

#include <iomanip>
#include <sstream>

std::string ScheduleStrFormat::formatRecord(const Flight & flight) {
	std::string dst(RECORD_LENGTH, ' ');

	repalaceInString(dst, std::to_string(flight.getNo()), NUMBER_OFFSET);
	repalaceInString(dst, flight.getCompany(), COMPANY_NAME_OFFSET);
	repalaceInString(dst, flight.getDeparture(), DEPARTURE_AIRPORT_OFFSET);
	repalaceInString(dst, flight.getArrival(), ARRIVAL_AIRPORT_OFFSET);
	std::string dateStr = formatDateTime(flight.getDateTime());
	repalaceInString(dst, dateStr, DEPARTURE_DATE_OFFSET);
	repalaceInString(dst, "\n", NEW_LINE_OFFSET);

	return dst;
}

std::string ScheduleStrFormat::formatRecordUI(const Flight & flight) {
	std::ostringstream outStream;

	outStream << std::setw(4) << std::setfill('0') <<  flight.getNo() << "  "
			<< flight.getDeparture() << " " << flight.getArrival() << " "  << flight.getCompany() << " "
			<< formatDateTimeUI(flight.getDateTime()) << "\n";

	return outStream.str();
}

std::string ScheduleStrFormat::getCompany(const std::string & scheduleRecord) {
	return scheduleRecord.substr(COMPANY_NAME_OFFSET, Config::COMPANY_NAME_LENGTH);
}

std::string ScheduleStrFormat::getDate(const std::string & scheduleRecord) {
	return scheduleRecord.substr(DEPARTURE_DATE_OFFSET, Config::DATE_LENGTH);
}

std::string ScheduleStrFormat::getTime(const std::string & scheduleRecord) {
	return scheduleRecord.substr(DEPARTURE_TIME_OFFSET, Config::TIME_LENGTH);
}

std::string ScheduleStrFormat::getDepartureCity(const std::string & scheduleRecord) {
	return scheduleRecord.substr(DEPARTURE_AIRPORT_OFFSET, Config::AIRPORT_LENGTH);
}

std::string ScheduleStrFormat::getArrivalCity(const std::string & scheduleRecord) {
	return scheduleRecord.substr(ARRIVAL_AIRPORT_OFFSET, Config::AIRPORT_LENGTH);
}
