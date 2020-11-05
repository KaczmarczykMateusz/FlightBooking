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

//TODO: get rid of that kind of archaic C-style structuring

static const uint32_t NAME_LENGTH = 30 + 1;
static const uint32_t NUMBER_OFFSET = 0;
static const uint32_t NUMBER_LENGTH = 5 + 1;
static const uint32_t COMPANY_NAME_OFFSET = NUMBER_OFFSET + NUMBER_LENGTH;
static const uint32_t COMPANY_NAME_LENGTH = 20 + 1;
static const uint32_t DEPARTURE_AIRPORT_OFFSET = COMPANY_NAME_OFFSET + COMPANY_NAME_LENGTH;
static const uint32_t DEPARTURE_AIRPORT_LENGTH = 20 + 1;
static const uint32_t ARRIVAL_AIRPORT_OFFSET = DEPARTURE_AIRPORT_OFFSET + DEPARTURE_AIRPORT_LENGTH;
static const uint32_t ARRIVAL_AIRPORT_LENGTH = 20 + 1;
static const uint8_t  DEPARTURE_DATE_OFFSET = ARRIVAL_AIRPORT_OFFSET + ARRIVAL_AIRPORT_LENGTH;
static const uint32_t DEPARTURE_DATE_LENGTH = 6;
static const uint8_t  DEPARTURE_TIME_OFFSET = DEPARTURE_DATE_OFFSET + DEPARTURE_DATE_LENGTH;
static const uint32_t DEPARTURE_TIME_LENGTH = 4;
static const uint32_t NEW_LINE_OFFSET = DEPARTURE_TIME_OFFSET + DEPARTURE_TIME_LENGTH;
static const uint32_t NEW_LINE_LENGTH = 1;

static const uint32_t RECORD_LENGTH = NEW_LINE_OFFSET + NEW_LINE_LENGTH;
static const uint32_t RECORD_OFFSET = RECORD_LENGTH + 1;

static const std::string newLineStr = "\n\n\n\n\n\n\n\n\n";
static const char SEPARATOR = ' ';


//Mode of searching
enum SearchBy {
	COMPANY,
	DEPARTURE_AIRPORT,
	ARRIVAL_AIRPORT,
	DEPARTURE_DATE
};

#endif /* APPLICATION_COMMON_HPP_ */
