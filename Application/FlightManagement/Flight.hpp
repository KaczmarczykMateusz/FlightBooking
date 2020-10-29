/*
 * Flight.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_FLIGHT_HPP_
#define APPLICATION_FLIGHT_HPP_

#include "../Common/DateTime.hpp"
#include "../Common/Common.hpp"

//TODO: make use of this class !!

class Flight {
	uint16_t Number;
	char Company[COMPANY_NAME_LENGTH];
	DateTime Departure;

public:
	Flight();

	void DisplayDetails(uint16_t flightNo);
	void SetNumber(uint16_t numb);
	void SetCompanyName(const char * name);
	void SetDeparture(const DateTime & depart);
};

#endif /* APPLICATION_FLIGHT_HPP_ */
