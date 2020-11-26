/*
 * Flight.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_FLIGHT_HPP_
#define APPLICATION_FLIGHT_HPP_

#include "../Common/Date.hpp"
#include "../Common/Time.hpp"

#include <cstdint>
#include <string>


class Flight {
public:
	Flight(uint32_t id, std::string company, Date date, Time time, std::string departure, std::string arrival, uint16_t seats);

	Flight(std::string str);

	uint16_t getId() const;
	std::string getCompany() const;
	Date getDate() const;
	Time getTime() const;
	std::string getDeparture() const;
	std::string getArrival() const;
	uint16_t getLeftSeats() const;

private:
	uint32_t id;
	std::string company;
	Date date;
	Time time;
	std::string departure;
	std::string arrival;

	uint16_t seats;  //TODO: implement seats in flight schedule file
	uint16_t occupiedSeats;
};

#endif /* APPLICATION_FLIGHT_HPP_ */
