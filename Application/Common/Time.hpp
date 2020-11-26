/*
 * Time.hpp
 *
 *  Created on: 25 lis 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_COMMON_TIME_HPP_
#define APPLICATION_COMMON_TIME_HPP_

#include <cstdint>

class Time {
	uint8_t hour;
	uint8_t minute;

public:
	Time(uint8_t hour, uint8_t minute) :
		hour(hour),
		minute(minute)
	{}

	Time() :
		hour(0),
		minute(0)
	{}

	uint8_t getHour() const {
		return hour;
	}

	uint8_t getMinute() const {
		return minute;
	}
};

#endif /* APPLICATION_COMMON_TIME_HPP_ */
