/*
 * DateTime.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_DATETIME_HPP_
#define APPLICATION_DATETIME_HPP_


class DateTime {
	class Time {
		int Hour;
		int Minute;
	public:
		Time(int Hour, int Minute) :
			Hour(Hour),
			Minute(Minute)
		{}
		int getHour() const {
			return Hour;
		}
		int getMinute() const {
			return Minute;
		}
	};

	class Date {
		int Year;
		int Month;
		int Day;

	public:
		Date(int Year, int Month, int Day) :
			Year(Year),
			Month(Month),
			Day(Day)
		{}

		int getYear() const {
			return Year;
		}
		int getMonth() const {
			return Month;
		}
		int getDay() const {
			return Day;
		}
	};

	Date date;
	Time time;

public:
	DateTime() :
		  date(-1, -1, -1)
		, time(-1, -1)
	{  }
	DateTime(int Year, int Month, int Day, int Hour, int Minute) :
		  date(Year, Month, Day)
		, time(Hour, Minute)
	{  }
	Date getDate() const {
		return date;
	}

	Time getTime() const {
		return time;
	}
};


#endif /* APPLICATION_DATETIME_HPP_ */
