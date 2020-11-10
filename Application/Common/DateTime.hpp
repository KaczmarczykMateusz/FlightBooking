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
	uint8_t Hour;
	uint8_t Minute;
public:
	Time(uint8_t Hour, uint8_t Minute) :
		Hour(Hour),
		Minute(Minute)
	{}
	uint8_t getHour() const {
		return Hour;
	}
	uint8_t getMinute() const {
		return Minute;
	}
};

class Date {
	uint16_t Year;
	uint8_t Month;
	uint8_t Day;

public:
	Date(uint16_t Year, uint8_t Month, uint8_t Day) :
		Year(Year),
		Month(Month),
		Day(Day)
	{}

	uint16_t getYear() const {
		return Year;
	}
	uint8_t getMonth() const {
		return Month;
	}
	uint8_t getDay() const {
		return Day;
	}
};

class DateTime {
public:
	DateTime() :
		  date(0, 0, 0)
		, time(0, 0)
	{  }
	DateTime(uint16_t Year, uint8_t Month, uint8_t Day, uint8_t Hour, uint8_t Minute) :
		  date(Year, Month, Day)
		, time(Hour, Minute)
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
