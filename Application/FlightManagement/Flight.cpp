/*
 * Flight.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "Flight.hpp"

#include <cstdint>
#include <iostream>

#include <cstring> //TODO: get rid of it along with strcpy


Flight::Flight() :
	Number(0),
	Company("\0")
	{}
void Flight::DisplayDetails(uint16_t flightNo) { //TODO: decide whether to use this function
	std::cout << "Flight No.:\t\tCompany name:\t\tDeparture date:\t\tDeparture time:" << std::endl;
	std::cout << Number << "\t\t\t" << Company << "\t\t" <<  Departure.getDate().getDay() << "/"
			<< Departure.getDate().getMonth() << "/" <<  Departure.getDate().getYear() << "\t\t\t"
			<< Departure.getTime().getHour() << ":" <<  Departure.getTime().getMinute() << std::endl; //TODO: leading 0
}

void Flight::SetNumber(uint16_t numb) {
	Number = numb;
}

void Flight::SetCompanyName(const char * name) {
	strcpy(Company, name);
}

void Flight::SetDeparture(const DateTime & depart) {
	Departure = depart;
}
