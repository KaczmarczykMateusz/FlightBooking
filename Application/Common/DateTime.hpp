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
		Time() :
			Hour(0),
			Minute(0)
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
		Date() :
			Year(0),
			Month(0),
			Day(0)
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
	Date getDate() const {
		return date;
	}

	Time getTime() const {
		return time;
	}
};


#endif /* APPLICATION_DATETIME_HPP_ */
