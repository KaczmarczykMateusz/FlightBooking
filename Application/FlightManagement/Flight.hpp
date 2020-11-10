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
	Flight(uint32_t number, std::string company, DateTime dateTime, std::string departure, std::string arrival, uint16_t seats);

	Flight(std::string str);

	uint16_t getNo() const;
	std::string getCompany() const;
	DateTime getDateTime() const;
	std::string getDeparture() const;
	std::string getArrival() const;
	uint16_t getLeftSeats() const;

private:
	uint32_t number;
	std::string company;
	DateTime dateTime;
	std::string departure;
	std::string arrival;

	uint16_t seats;
	uint16_t occupiedSeats;
};

#endif /* APPLICATION_FLIGHT_HPP_ */
