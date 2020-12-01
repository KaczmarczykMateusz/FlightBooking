/*
 * Flight.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "Flight.hpp"
#include "../StringFormat/StringFormatter.hpp"
#include "../Common/Common.hpp"

#include <cstdint>
#include <sstream>
#include <iomanip>  //setw, setfill
#include <iostream>

#include "../StringFormat/ScheduleStrFormat.hpp"

Flight::Flight(uint32_t id, std::string company, Date date, Time time, std::string departure, std::string arrival, uint16_t seats) :
	  id(id)
	, company(company)
	, date(date)
	, time(time)
	, departure(departure)
	, arrival(arrival)
	, seats(seats)
	{}

Flight::Flight(std::string str)
{
	assert(!str.empty());
	std::string idStr = ScheduleStrFormat::getId(str);
	company = ScheduleStrFormat::getCompany(str);

	std::string dateStr = ScheduleStrFormat::getDate(str);
	try {
		id = stoi(idStr);

		int tmp = stoi(dateStr);
		int Year = tmp % 100;
		tmp /= 100;
		int Month = tmp % 100;
		int Day = tmp / 100;

		std::string timeStr = ScheduleStrFormat::getTime(str);
		tmp = stoi(timeStr);
		int Minute = tmp % 100;
		int Hour = tmp / 100;
		date = Date(Year, Month, Day);
		time = Time(Hour, Minute);
	}
	catch(...) {
	};

	departure = ScheduleStrFormat::getDepartureCity(str);
	arrival = ScheduleStrFormat::getArrivalCity(str);
	seats = ScheduleStrFormat::getSeats(str);
}

uint16_t Flight::getId() const {
	return id;
}

std::string Flight::getCompany() const {
	return company;
}

Date Flight::getDate() const {
	return date;
}

Time Flight::getTime() const {
	return time;
}

std::string Flight::getDeparture() const {
	return departure;
}

std::string Flight::getArrival() const {
	return arrival;
}

uint16_t Flight::getLeftSeats() const {
	return seats;
}

