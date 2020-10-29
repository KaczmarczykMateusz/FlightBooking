/*
 * Flight.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_FLIGHT_HPP_
#define APPLICATION_FLIGHT_HPP_

#include "DateTime.hpp"
#include "Common.hpp"

#include <cstdint>
#include <iostream>

class Flight {
	uint16_t Number;
	char Company[COMPANY_NAME_LENGTH];
	DateTime Departure;

public:
	Flight() :
		Number(0),
		Company("\0")
		{}
	void DisplayDetails(uint16_t flightNo) { //TODO: decide whether to use this function
		std::cout << "Flight No.:\t\tCompany name:\t\tDeparture date:\t\tDeparture time:" << std::endl;
		std::cout << Number << "\t\t\t" << Company << "\t\t" <<  Departure.getDate().getDay() << "/"
				<< Departure.getDate().getMonth() << "/" <<  Departure.getDate().getYear() << "\t\t\t"
				<< Departure.getTime().getHour() << ":" <<  Departure.getTime().getMinute() << std::endl; //TODO: leading 0
	}

	void SetNumber(uint16_t numb) {
		Number = numb;
	}

	void SetCompanyName(const char * name) {
		strcpy(Company, name);
	}

	void SetDeparture(const DateTime & depart) {
		Departure = depart;
	}
};

#endif /* APPLICATION_FLIGHT_HPP_ */
