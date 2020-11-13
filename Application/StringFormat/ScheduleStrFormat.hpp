/*
 * ScheduleStrFormat.hpp
 *
 *  Created on: 12 Nov 2020
 *      Author: Mateusz Kaczmarczyk
 *
 *  Description: Class for handling file
 *  containing list of all flights registered
 *  in system.
 */

#ifndef APPLICATION_STRINGFORMAT_SCHEDULESTRFORMAT_HPP_
#define APPLICATION_STRINGFORMAT_SCHEDULESTRFORMAT_HPP_

#include "StringFormatter.hpp"

#include <string>
#include <cassert>

class Flight;

class ScheduleStrFormat: public StringFormatter {
public:
	ScheduleStrFormat() = default;

	static const uint32_t NUMBER_OFFSET = 0;
	static const uint32_t COMPANY_NAME_OFFSET = NUMBER_OFFSET + Config::FLIGHT_ID_LENGTH;
	static const uint32_t DEPARTURE_AIRPORT_OFFSET = COMPANY_NAME_OFFSET + Config::COMPANY_NAME_LENGTH;
	static const uint32_t ARRIVAL_AIRPORT_OFFSET = DEPARTURE_AIRPORT_OFFSET + Config::AIRPORT_LENGTH;
	static const uint8_t  DEPARTURE_DATE_OFFSET = ARRIVAL_AIRPORT_OFFSET + Config::AIRPORT_LENGTH;
	static const uint8_t  DEPARTURE_TIME_OFFSET = DEPARTURE_DATE_OFFSET + Config::DATE_LENGTH;
	static const uint32_t NEW_LINE_OFFSET = DEPARTURE_TIME_OFFSET + Config::TIME_LENGTH;

	static const uint32_t RECORD_LENGTH = NEW_LINE_OFFSET + Config::NEW_LINE_LENGTH;
	static const uint32_t RECORD_OFFSET = RECORD_LENGTH + 1;

	static std::string formatRecord(const Flight & flight);
	static std::string formatRecordUI(const Flight & flight);

	static std::string getCompany(const std::string & scheduleRecord);
	static std::string getDate(const std::string & scheduleRecord);
	static std::string getTime(const std::string & scheduleRecord);
	static std::string getDepartureCity(const std::string & scheduleRecord);
	static std::string getArrivalCity(const std::string & scheduleRecord);
};

#endif /* APPLICATION_STRINGFORMAT_SCHEDULESTRINGFORMATTER_HPP_ */
