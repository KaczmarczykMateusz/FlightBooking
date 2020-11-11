/*
 * Common.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Matueusz Kaczmarczyk
 */

#ifndef APPLICATION_COMMON_HPP_
#define APPLICATION_COMMON_HPP_

#include <cstdint>
#include <string>

struct Config {
	static const uint32_t NUMBER_LENGTH = 5;
	static const uint32_t FIRST_NAME_LENGTH = 15;
	static const uint32_t SURNAME_LENGTH = 15;
	static const uint32_t COMPANY_NAME_LENGTH = 16;
	static const uint32_t AIRPORT_LENGTH = 20;
	static const uint32_t DATE_LENGTH = 6;
	static const uint32_t TIME_LENGTH = 4;
	static const uint32_t NEW_LINE_LENGTH = 1;
};

struct PassangerDef {
	static const uint32_t NUMBER_OFFSET = 0;
	static const uint32_t FIRSTNAME_OFFSET = NUMBER_OFFSET + Config::FIRST_NAME_LENGTH;;
	static const uint32_t SURNAME_OFFSET = FIRSTNAME_OFFSET + Config::SURNAME_LENGTH;
};

struct FlightDef {
	static const uint32_t NUMBER_OFFSET = 0;
	static const uint32_t COMPANY_NAME_OFFSET = NUMBER_OFFSET + Config::NUMBER_LENGTH;
	static const uint32_t DEPARTURE_AIRPORT_OFFSET = COMPANY_NAME_OFFSET + Config::COMPANY_NAME_LENGTH;
	static const uint32_t ARRIVAL_AIRPORT_OFFSET = DEPARTURE_AIRPORT_OFFSET + Config::AIRPORT_LENGTH;
	static const uint8_t  DEPARTURE_DATE_OFFSET = ARRIVAL_AIRPORT_OFFSET + Config::AIRPORT_LENGTH;
	static const uint8_t  DEPARTURE_TIME_OFFSET = DEPARTURE_DATE_OFFSET + Config::DATE_LENGTH;
	static const uint32_t NEW_LINE_OFFSET = DEPARTURE_TIME_OFFSET + Config::TIME_LENGTH;

	static const uint32_t RECORD_LENGTH = NEW_LINE_OFFSET + Config::NEW_LINE_LENGTH;
	static const uint32_t RECORD_OFFSET = RECORD_LENGTH + 1;
};

static const std::string FlightHeader = "\n\nNo.:  Departure city:       Arrival City:         "
										"Company:          Date:      Time:\n";

static const char SEPARATOR = ' ';


//Mode of searching
enum SearchBy {
	COMPANY,
	DEPARTURE_AIRPORT,
	ARRIVAL_AIRPORT,
	DEPARTURE_DATE
};

#endif /* APPLICATION_COMMON_HPP_ */
