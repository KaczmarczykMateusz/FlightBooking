/*
 * Passenger.cpp
 *
 *  Created on: 12 lis 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "Passenger.h"
#include "../StringFormat/PassengerListStrFormat.hpp"

Passenger::Passenger(std::string firstName, std::string surname, uint64_t personalId) :
	  firstName(firstName)
	, surname(surname)
	, personalId(personalId)
	, checkedIn(false)
{  }

Passenger::Passenger(std::string str) {
	firstName = PassengerListStrFormat::getFirstName(str);
	surname = PassengerListStrFormat::getSurname(str);
	personalId = PassengerListStrFormat::getPersonalId(str);
	checkedIn = PassengerListStrFormat::getCheckedIn(str);
}

std::string Passenger::getFirstName() const  {
	return firstName;
}

std::string Passenger::getSurname() const  {
	return surname;
}

uint64_t Passenger::getPersonalId() const  {
	return personalId;
}

bool Passenger::getCheckedIn() const  {
	return checkedIn;
}

void Passenger::setCheckedIn(bool checkIn) {
	checkedIn = checkIn;
}
