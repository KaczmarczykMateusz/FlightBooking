/*
 * Passenger.cpp
 *
 *  Created on: 12 lis 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "Passenger.h"

Passenger::Passenger(std::string firstName, std::string surname, uint32_t id) :
	  firstName(firstName)
	, surname(surname)
	, id(id)
	, checkedIn(false)
{  }

Passenger::Passenger(std::string str) {

}

std::string Passenger::getFirstName() const  {
	return firstName;
}

std::string Passenger::getSurname() const  {
	return surname;
}

uint32_t Passenger::getId() const  {
	return id;
}

bool Passenger::getCheckedIn() const  {
	return checkedIn;
}
