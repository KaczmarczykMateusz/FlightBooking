/*
 * PassengerListFile.hpp
 *
 *  Created on: 07 Nov 2020
 *      Author: Mateusz Kaczmarczyk
 *
 *  Description: Class for handling file
 *  containing flight details which is
 *  passenger list
 */

#ifndef APPLICATION_FILE_PASSENGERLISTFILE_HPP_
#define APPLICATION_FILE_PASSENGERLISTFILE_HPP_

#include "../UserInterface.hpp"
#include "File.hpp"
#include "../Common/Common.hpp"

#include <fstream>
#include <vector>

class Passenger;

class PassengerListFile : public File {

public:
	PassengerListFile(uint32_t flightNo);

	virtual ~PassengerListFile() = default;

	// Return: false if record doesn't exist
	virtual bool getRecord(std::string &dst, uint16_t recordNumber) override;

	uint32_t getNewRecordOffset();

	Passenger searchPassanger(std::string name, std::string surname);

	void registerPassanger(const Passenger & flight);
};


#endif /* PASSENGERLISTFILE */
