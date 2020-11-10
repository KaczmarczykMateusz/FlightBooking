/*
 * DateTime.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_DATETIME_HPP_
#define APPLICATION_DATETIME_HPP_

#include <cstdint>

//TODO: consider to export to different files
class Time {
	uint8_t hour;
	uint8_t minute;
public:
	Time(uint8_t hour, uint8_t minute) :
		hour(hour),
		minute(minute)
	{}
	uint8_t getHour() const {
		return hour;
	}
	uint8_t getMinute() const {
		return minute;
	}
};

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

class DateTime {
public:
	DateTime() :
		  date(0, 0, 0)
		, time(0, 0)
	{  }
	DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute) :
		  date(year, month, day)
		, time(hour, minute)
	{  }
	DateTime(Date date, Time time) :
		  date(date)
		, time(time)
	{  }
	Date getDate() const {
		return date;
	}

	Time getTime() const {
		return time;
	}
private:
	Date date;
	Time time;
};


#endif /* APPLICATION_DATETIME_HPP_ */
