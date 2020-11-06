/*
 * FileInterface.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_FILEINTERFACE_HPP_
#define APPLICATION_FILEINTERFACE_HPP_

#include "UserInterface.hpp"
#include "Common/Common.hpp"

#include <fstream>
#include <vector>

class FileInterface {
	UserInterface UI;
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

	std::string search(SearchBy key, const std::string);

	uint32_t SearchGreatestNo();

	bool SearchDetail(std::string & dst, uint32_t offset, uint16_t length);

	std::vector<std::string> SearchFlight(std::string departureAirport, std::string arrivalAirport);

	void writeFlights(const std::string input, uint8_t length) ;
};


#endif /* APPLICATION_FILEINTERFACE_HPP_ */
