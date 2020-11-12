/*
 * PassengerListStrFormat.cpp
 *
 *  Created on: 12 Nov 2020
 *      Author: Mateusz
 */

#include "../Common/DateTime.hpp"
#include "../FlightManagement/Flight.hpp"
#include "../Common/Common.hpp"
#include "../FlightManagement/Passenger.h"
#include "PassengerListStrFormat.hpp"

#include <iomanip>
#include <sstream>

std::string PassengerListStrFormat::formatRecord(const Passenger & passenger) {
	std::string dst(RECORD_LENGTH, ' ');

	repalaceInString(dst, passenger.getFirstName(), FIRST_NAME_OFFSET);
	repalaceInString(dst, passenger.getSurname(), SURNAME_OFFSET);
	repalaceInString(dst, std::to_string(passenger.getId()), ID_OFFSET);
	std::string checkedIn = std::to_string(passenger.getCheckedIn() ? 1 : 0);
	repalaceInString(dst, checkedIn, CHECKED_IN_OFFSET);
	repalaceInString(dst, "\n", NEW_LINE_OFFSET);

	return dst;
}

std::string PassengerListStrFormat::formatRecordUI(const Passenger & passenger) {
	std::ostringstream outStream;

	outStream << passenger.getFirstName() << "  "
			<< passenger.getSurname() << " "
			<< passenger.getId() << "  "
			<< passenger.getCheckedIn() << "\n";

	return outStream.str();
}
