/*
 * PassengerListStrFormat.hpp
 *
 *  Created on: 12 Nov 2020
 *      Author: Mateusz Kaczmarczyk
 *
 *  Description: Class for handling file
 *  containing list of all flights registered
 *  in system.
 */

#ifndef APPLICATION_STRINGFORMAT_PASSENGERLISTTSTRFORMAT_HPP_
#define APPLICATION_STRINGFORMAT_PASSENGERLISTTSTRFORMAT_HPP_

#include "StringFormatter.hpp"

#include <string>

class Passenger;

class PassengerListStrFormat: public StringFormatter {
public:
	PassengerListStrFormat() = default;

	static const uint32_t FIRST_NAME_OFFSET = 0;
	static const uint32_t SURNAME_OFFSET = FIRST_NAME_OFFSET + Config::FIRST_NAME_LENGTH;
	static const uint32_t ID_OFFSET = SURNAME_OFFSET + Config::SURNAME_LENGTH;
	static const uint32_t CHECKED_IN_OFFSET = ID_OFFSET + Config::PASSENGER_ID_LENGTH;
	static const uint32_t CHECKED_IN_LENGTH = 1;
	static const uint32_t NEW_LINE_OFFSET = CHECKED_IN_OFFSET + CHECKED_IN_LENGTH;

	static const uint32_t RECORD_LENGTH = NEW_LINE_OFFSET + Config::NEW_LINE_LENGTH;
	static const uint32_t RECORD_OFFSET = RECORD_LENGTH + 1;

	static std::string formatRecord(const Passenger & passenger);
	static std::string formatRecordUI(const Passenger & passenger);

};

#endif /* APPLICATION_STRINGFORMAT_PASSENGERLISTTSTRFORMAT_HPP_ */
