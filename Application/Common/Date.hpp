/*
 * Date.hpp
 *
 *  Created on: 25 lis 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_COMMON_DATE_HPP_
#define APPLICATION_COMMON_DATE_HPP_

#include <cstdint>

class Date {
	uint16_t year;
	uint8_t month;
	uint8_t day;

public:
	Date(uint16_t year, uint8_t month, uint8_t day) :
		year(year),
		month(month),
		day(day)
	{}

	Date() :
		year(0),
		month(0),
		day(0)
	{}

	uint16_t getYear() const {
		return year;
	}

	uint8_t getMonth() const {
		return month;
	}

	uint8_t getDay() const {
		return day;
	}
};


#endif /* APPLICATION_COMMON_DATE_HPP_ */
