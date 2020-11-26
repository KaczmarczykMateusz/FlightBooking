/*
 * PassengerListFile.cpp
 *
 *  Created on: 07 Nov 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "PassengerListFile.hpp"
#include "../StringFormat/PassengerListStrFormat.hpp"
#include "../FlightManagement/Passenger.h"


#include <cassert>
#include <sstream>

PassengerListFile::PassengerListFile(uint32_t flightNo) :
	File()
{
	std::ostringstream name;
	name << "DB/PassengerLists/flight_no_" << std::to_string(flightNo) << ".dat";
	File::setName(name.str());
}

bool PassengerListFile::registerPassanger(const Passenger & passenger) {
	bool rc = false;
	std::string record = PassengerListStrFormat::formatRecord(passenger);
	if(!record.empty()) {
		rc = File::write(record);
	}
	return rc;
}

bool PassengerListFile::setCheckedIn(Passenger & passenger) {
	bool rc = false;

	std::string toDelete = PassengerListStrFormat::formatRecord(passenger);
	rc = File::eraseRecord(toDelete, PassengerListStrFormat::RECORD_LENGTH);

	passenger.setCheckedIn(true);
	registerPassanger(passenger);

	return rc;
}

