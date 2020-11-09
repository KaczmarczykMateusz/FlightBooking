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
#include "File.hpp"
#include "../Common/Common.hpp"

#include <fstream>
#include <vector>

class FlightFile : public File {

public:
	FlightFile();

	virtual ~FlightFile() = default;

	// Return: false if record doesn't exist
	virtual bool GetRecord(std::string &dst, uint16_t recordNumber) override;

	uint32_t SearchGreatestNo();

	std::string SearchDetail(uint32_t offset, uint16_t length);  //TODO: remove this function as far as it is totally unnecessary

	std::vector<Flight> SearchFlight(std::string departureAirport, std::string arrivalAirport);

	void RegisterFlight(const std::string input);
};


#endif /* APPLICATION_FILEINTERFACE_HPP_ */
