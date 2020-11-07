/*
 * Flight.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "Flight.hpp"
#include "../Common/Common.hpp"

#include <cstdint>
#include <sstream>
#include <iomanip>  //setw, setfill


Flight::Flight(uint32_t Number, std::string Company, DateTime Date, std::string Departure, std::string Arrival, uint16_t Seats) :
	Number(Number)
	, Company(Company)
	, Date(Date)
	, Departure(Departure)
	, Arrival(Arrival)
	, Seats(Seats)
	, OccupiedSeats(0)
	{}

void Flight::Print(std::ostringstream & out) {
	out << std::setw(4) << std::setfill('0') <<  Number << "  "
			<< Departure << " " << Arrival << " "  << Company << " "
			<< std::setw(2) << std::setfill('0')
			<< Date.getDate().getDay() << "/"
			<< std::setw(2) << std::setfill('0')
			<< Date.getDate().getMonth() << "/"
			<<  Date.getDate().getYear() << "   " << std::setw(2) << std::setfill('0')
			<< Date.getTime().getHour() << ":" <<  Date.getTime().getMinute() << "\n";
}

Flight::Flight(std::string str) :
	OccupiedSeats(0)
{
	std::string company = str.substr(COMPANY_NAME_OFFSET, COMPANY_NAME_LENGTH);
	std::string deaprture = str.substr(DEPARTURE_AIRPORT_OFFSET, DEPARTURE_AIRPORT_LENGTH);
	std::string arrival = str.substr(ARRIVAL_AIRPORT_OFFSET, ARRIVAL_AIRPORT_LENGTH);
	std::string date = str.substr(DEPARTURE_DATE_OFFSET, DEPARTURE_DATE_LENGTH);
	std::string time = str.substr(DEPARTURE_TIME_OFFSET, DEPARTURE_TIME_LENGTH);

	int tmp = stoi(date);
	int Year = tmp % 100;
	tmp /= 100;
	int Month = tmp % 100;
	int Day = tmp / 100;

	tmp = stoi(time);
	int Minute = tmp % 100;
	int Hour = tmp / 100;

	Number = 0;
	Company = company;
	Date = DateTime(Year, Month, Day, Hour, Minute);
	Departure = deaprture;
	Arrival = arrival;
	Seats = 300;
}

void Flight::ChangeDate(const DateTime & depart) {
	Date = depart;
}
