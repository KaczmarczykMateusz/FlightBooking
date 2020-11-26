/*
 * PassengerListStrFormat.cpp
 *
 *  Created on: 12 Nov 2020
 *      Author: Mateusz
 */

#include "../FlightManagement/Flight.hpp"
#include "../Common/Date.hpp"
#include "../Common/Time.hpp"
#include "../Common/Common.hpp"
#include "../FlightManagement/Passenger.h"
#include "PassengerListStrFormat.hpp"

#include <iomanip>
#include <sstream>

std::string PassengerListStrFormat::formatRecord(const Passenger & passenger) {
	std::string dst(RECORD_LENGTH, ' ');

	bool success = repalaceInString(dst, passenger.getFirstName(), FIRST_NAME_OFFSET);
	success &= repalaceInString(dst, passenger.getSurname(), SURNAME_OFFSET);
	success &= repalaceInString(dst, std::to_string(passenger.getPersonalId()), PERSONAL_ID_OFFSET);
	std::string checkedIn = std::to_string(passenger.getCheckedIn() ? 1 : 0);
	success &= repalaceInString(dst, checkedIn, CHECKED_IN_OFFSET);
	success &= repalaceInString(dst, "\n", NEW_LINE_OFFSET);

	if(!success) {
		dst.clear();
	}

	return dst;
}

std::string PassengerListStrFormat::formatRecordUI(const Passenger & passenger) {
	std::ostringstream outStream;

	outStream << passenger.getFirstName() << "  "
			<< passenger.getSurname() << " "
			<< passenger.getPersonalId() << "  "
			<< passenger.getCheckedIn() << "\n";

	return outStream.str();
}

std::string PassengerListStrFormat::getFirstName(const std::string & passengerListRecord) {
	return getSubStr(passengerListRecord, FIRST_NAME_OFFSET, Config::FIRST_NAME_LENGTH);
}

std::string PassengerListStrFormat::getSurname(const std::string & passengerListRecord) {
	return getSubStr(passengerListRecord, SURNAME_OFFSET, Config::SURNAME_LENGTH);
}

uint64_t PassengerListStrFormat::getPersonalId(const std::string & passengerListRecord) {
	std::string str = getSubStr(passengerListRecord, PERSONAL_ID_OFFSET, Config::PERSONAL_ID_LENGTH);
	uint64_t rc = 0;
	try {
		rc = stoull(str);
	}
	catch(...) {
	}
	return rc;
}

bool PassengerListStrFormat::getCheckedIn(const std::string & passengerListRecord) {
	std::string str = getSubStr(passengerListRecord, CHECKED_IN_OFFSET, CHECKED_IN_LENGTH);
	bool checkedIn = false;
	try {
		checkedIn = stoul(str) ? true : false;
	}
	catch(...) {
	}
	return checkedIn;
}
