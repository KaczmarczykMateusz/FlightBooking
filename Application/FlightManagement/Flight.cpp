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


Flight::Flight(uint32_t Number, std::string Company, DateTime date, std::string Departure, std::string Arrival, uint16_t Seats) :
	Number(Number)
	, Company(Company)
	, date(date)
	, Departure(Departure)
	, Arrival(Arrival)
	, Seats(Seats)
	, OccupiedSeats(0)
	{}

void Flight::Print(std::ostringstream & out) {
	out << std::setw(4) << std::setfill('0') <<  Number << "  "
			<< Departure << " " << Arrival << " "  << Company << " "
			<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getDate().getDay()) << "/"
			<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getDate().getMonth()) << "/"
			<< static_cast<int>(date.getDate().getYear()) << "   "
			<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getTime().getHour()) << ":"
			<< std::setw(2) << std::setfill('0') << static_cast<int>(date.getTime().getMinute()) << "\n";
}

Flight::Flight(std::string str) :
	OccupiedSeats(0)
{
	Number = 0;
	Company = str.substr(COMPANY_NAME_OFFSET, COMPANY_NAME_LENGTH);

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

	date = DateTime(Year, Month, Day, Hour, Minute);

	Departure = str.substr(DEPARTURE_AIRPORT_OFFSET, DEPARTURE_AIRPORT_LENGTH);
	Arrival = str.substr(ARRIVAL_AIRPORT_OFFSET, ARRIVAL_AIRPORT_LENGTH);
	Seats = 300;
}

void Flight::ChangeDate(const DateTime & depart) {
	date = depart;
}

uint16_t Flight::GetNo() const {
	return Number;
}

std::string Flight::GetCompany() const {
	return Company;
}

DateTime Flight::getDateTime() const {
	return date;
}

std::string Flight::GetDeparture() const {
	return Departure;
}

std::string Flight::GetArrival() const {
	return Arrival;
}

uint16_t Flight::GetLeftSeats() const {
	return (Seats - OccupiedSeats);
}

