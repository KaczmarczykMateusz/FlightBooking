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
	static const uint32_t FLIGHT_ID_LENGTH = 5;
	static const uint32_t FIRST_NAME_LENGTH = 15;
	static const uint32_t SURNAME_LENGTH = 15;
	static const uint32_t PERSONAL_ID_LENGTH = 10;
	static const uint32_t COMPANY_NAME_LENGTH = 16;
	static const uint32_t AIRPORT_LENGTH = 20;
	static const uint32_t DATE_LENGTH = 6;
	static const uint32_t TIME_LENGTH = 4;
	static const uint32_t NEW_LINE_LENGTH = 1;
};


static const std::string FlightHeader = "\n\nNo.:  Departure city:      Arrival City:        "
										"Company:         Date:      Time:\n";

static const char SEPARATOR = ' ';


//Mode of searching
enum SearchBy {
	COMPANY,
	DEPARTURE_AIRPORT,
	ARRIVAL_AIRPORT,
	DEPARTURE_DATE
};

#endif /* APPLICATION_COMMON_HPP_ */
