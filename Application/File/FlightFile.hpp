/*
 * FlightFile.hpp
 *
 *  Created on: 07 Nov 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_FLIGHT_FILE_HPP_
#define APPLICATION_FLIGHT_FILE_HPP_

#include "../FlightManagement/Flight.hpp"
#include "../UserInterface.hpp"
#include "FileInterface.hpp"
#include "../Common/Common.hpp"

#include <fstream>
#include <vector>

class FlightFile : public FileInterface {

public:
	FlightFile();

	virtual ~FlightFile() = default;

	// Return: false if record doesn't exist
	virtual bool GetRecord(std::string &dst, uint16_t recordNumber) override;

	uint32_t SearchGreatestNo();

	bool SearchDetail(std::string & dst, uint32_t offset, uint16_t length);

	std::vector<Flight> SearchFlight(std::string departureAirport, std::string arrivalAirport);

	void WriteFlights(const std::string input, uint8_t length) ;

private:
	std::fstream flights;
};


#endif /* APPLICATION_FILEINTERFACE_HPP_ */
