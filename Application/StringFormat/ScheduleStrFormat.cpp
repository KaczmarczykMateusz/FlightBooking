/*
 * ScheduleStrFormat.cpp
 *
 *  Created on: 12 Nov 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "../FlightManagement/Flight.hpp"
#include "../Common/Date.hpp"
#include "../Common/Time.hpp"
#include "../Common/Common.hpp"
#include "ScheduleStrFormat.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>

using std::stringstream;

std::string ScheduleStrFormat::formatRecord(const Flight & flight) {
	std::string dst(RECORD_LENGTH, ' ');

	repalaceInString(dst, std::to_string(flight.getId()), ID_OFFSET);
	repalaceInString(dst, flight.getCompany(), COMPANY_NAME_OFFSET);
	repalaceInString(dst, flight.getDeparture(), DEPARTURE_AIRPORT_OFFSET);
	repalaceInString(dst, flight.getArrival(), ARRIVAL_AIRPORT_OFFSET);
	std::string dateStr = formatDate(flight.getDate());
	repalaceInString(dst, dateStr, DEPARTURE_DATE_OFFSET);
	std::string timeStr = formatTime(flight.getTime());
	repalaceInString(dst, timeStr, DEPARTURE_TIME_OFFSET);
	stringstream ss;
	ss <<  std::setw(4) << std::setfill(' ') << flight.getLeftSeats();
	repalaceInString(dst, ss.str(), SEATS_AVAILABLE_OFFSET);
	repalaceInString(dst, "\n", NEW_LINE_OFFSET);

	return dst;
}

std::string ScheduleStrFormat::formatRecordUI(const Flight & flight) {
	std::ostringstream outStream;

	outStream << std::setw(4) << std::setfill(' ') <<  flight.getId() << "  "
			<< flight.getDeparture() << " " << flight.getArrival() << " "  << flight.getCompany() << " "
			<< formatDateUI(flight.getDate()) << formatTimeUI(flight.getTime()) << "    "
			<< formatSeatsUI(flight.getLeftSeats()) << "\n";

	return outStream.str();
}

std::string ScheduleStrFormat::getId(const std::string & scheduleRecord) {
	return getSubStr(scheduleRecord, ID_OFFSET, Config::FLIGHT_ID_LENGTH);
}

std::string ScheduleStrFormat::getCompany(const std::string & scheduleRecord) {
	return getSubStr(scheduleRecord, COMPANY_NAME_OFFSET, Config::COMPANY_NAME_LENGTH);
}

std::string ScheduleStrFormat::getDate(const std::string & scheduleRecord) {
	return getSubStr(scheduleRecord, DEPARTURE_DATE_OFFSET, Config::DATE_LENGTH);
}

std::string ScheduleStrFormat::getTime(const std::string & scheduleRecord) {
	return getSubStr(scheduleRecord, DEPARTURE_TIME_OFFSET, Config::TIME_LENGTH);
}

std::string ScheduleStrFormat::getDepartureCity(const std::string & scheduleRecord) {
	return getSubStr(scheduleRecord, DEPARTURE_AIRPORT_OFFSET, Config::AIRPORT_LENGTH);
}

std::string ScheduleStrFormat::getArrivalCity(const std::string & scheduleRecord) {
	return getSubStr(scheduleRecord, ARRIVAL_AIRPORT_OFFSET, Config::AIRPORT_LENGTH);
}

uint16_t ScheduleStrFormat::getSeats(const std::string & scheduleRecord) {
	std::string str = getSubStr(scheduleRecord, SEATS_AVAILABLE_OFFSET, Config::SEATS_AVAILABLE_LENGTH);
	uint16_t seats = 0;
	try {
		seats = std::stoi(str);
	} catch(...) {
		seats = 0;
	};

	return seats;
}
