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

Flight::Flight(uint32_t id, std::string company, DateTime dateTime, std::string departure, std::string arrival, uint16_t seats) :
	id(id)
	, company(company)
	, dateTime(dateTime)
	, departure(departure)
	, arrival(arrival)
	, seats(seats)
	, occupiedSeats(0)
	{}

Flight::Flight(std::string str) :
	  occupiedSeats(0)
{
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

		std::string time = ScheduleStrFormat::getTime(str);
		tmp = stoi(time);
		int Minute = tmp % 100;
		int Hour = tmp / 100;
		dateTime = DateTime(Year, Month, Day, Hour, Minute);
	}
	catch(...) {
	};

	departure = ScheduleStrFormat::getDepartureCity(str);
	arrival = ScheduleStrFormat::getArrivalCity(str);
	seats = 300;
}

uint16_t Flight::getId() const {
	return id;
}

std::string Flight::getCompany() const {
	return company;
}

DateTime Flight::getDateTime() const {
	return dateTime;
}

std::string Flight::getDeparture() const {
	return departure;
}

std::string Flight::getArrival() const {
	return arrival;
}

uint16_t Flight::getLeftSeats() const {
	return (seats - occupiedSeats);
}

