/*
 * ScheduleFile.hpp
 *
 *  Created on: 07 Nov 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_FILE_SCHEDULEFILE_HPP_
#define APPLICATION_FILE_SCHEDULEFILE_HPP_

#include "../FlightManagement/Flight.hpp"
#include "../UserInterface.hpp"
#include "File.hpp"
#include "../Common/Common.hpp"

#include <fstream>
#include <vector>
#include <memory>

class ScheduleFile : public File {

public:
	ScheduleFile();

	virtual ~ScheduleFile() = default;

	// Return: false if record doesn't exist
	virtual bool getRecord(std::string &dst, uint16_t recordNumber) override;

	uint32_t getHightstId();


	std::vector<Flight> searchFlight(std::string departureAirport, std::string arrivalAirport);
	std::unique_ptr<Flight> searchFlight(uint32_t flightId);

	bool registerFlight(const Flight & flight);
	bool deleteRecord(const Flight & flight);
};


#endif /* APPLICATION_FILEINTERFACE_HPP_ */
