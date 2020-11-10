/*
 * Flight.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "Flight.hpp"
#include "../Common/StringFormatter.hpp"
#include "../Common/Common.hpp"

#include <cstdint>
#include <sstream>
#include <iomanip>  //setw, setfill


Flight::Flight(uint32_t number, std::string company, DateTime dateTime, std::string departure, std::string arrival, uint16_t seats) :
	number(number)
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
	number = 0;
	company = str.substr(COMPANY_NAME_OFFSET, COMPANY_NAME_LENGTH);

	std::string dateStr = str.substr(DEPARTURE_DATE_OFFSET, DEPARTURE_DATE_LENGTH);
	int tmp = stoi(dateStr);
	int Year = tmp % 100;
	tmp /= 100;
	int Month = tmp % 100;
	int Day = tmp / 100;

	std::string time = str.substr(DEPARTURE_TIME_OFFSET, DEPARTURE_TIME_LENGTH);
	tmp = stoi(time);
	int Minute = tmp % 100;
	int Hour = tmp / 100;

	dateTime = DateTime(Year, Month, Day, Hour, Minute);

	departure = str.substr(DEPARTURE_AIRPORT_OFFSET, DEPARTURE_AIRPORT_LENGTH);
	arrival = str.substr(ARRIVAL_AIRPORT_OFFSET, ARRIVAL_AIRPORT_LENGTH);
	seats = 300;
}

uint16_t Flight::getNo() const {
	return number;
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

