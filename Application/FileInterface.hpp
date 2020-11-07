/*
 * FileInterface.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_FILEINTERFACE_HPP_
#define APPLICATION_FILEINTERFACE_HPP_

#include "FlightManagement/Flight.hpp"
#include "UserInterface.hpp"
#include "Common/Common.hpp"

#include <fstream>
#include <vector>

class FileInterface {
	std::fstream flights;


	void openToWrite() {
		flights.open("flights.dat", std::fstream::out | std::fstream::app);
	}
	void openToRead() {
		flights.open("flights.dat", std::fstream::in | std::fstream::app);
	}
	void closeFile() {
		flights.close();
	}

public:

	// Return: false if record doesn't exist
	bool GetRecord(std::string &dst, uint16_t recordNumber);

	uint32_t SearchGreatestNo();

	bool SearchDetail(std::string & dst, uint32_t offset, uint16_t length);

	std::vector<Flight> SearchFlight(std::string departureAirport, std::string arrivalAirport);

	void WriteFlights(const std::string input, uint8_t length) ;
};


#endif /* APPLICATION_FILEINTERFACE_HPP_ */
