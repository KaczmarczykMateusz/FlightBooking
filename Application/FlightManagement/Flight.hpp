/*
 * Flight.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_FLIGHT_HPP_
#define APPLICATION_FLIGHT_HPP_

#include "../Common/DateTime.hpp"

#include <cstdint>
#include <string>


class Flight {
public:
	Flight(uint32_t Number, std::string Company, DateTime date, std::string Departure, std::string Arrival, uint16_t Seats);

	Flight(std::string str);

	void Print(std::ostringstream & out);
	void ChangeDate(const DateTime & depart);

	uint16_t GetNo() const;
	std::string GetCompany() const;
	DateTime getDateTime() const;
	std::string GetDeparture() const;
	std::string GetArrival() const;
	uint16_t GetLeftSeats() const;

private:
	uint32_t Number;
	std::string Company;
	DateTime date;
	std::string Departure;
	std::string Arrival;

	uint16_t Seats;
	uint16_t OccupiedSeats;
};

#endif /* APPLICATION_FLIGHT_HPP_ */
