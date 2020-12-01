/*
 * UserInterface.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_USERINTERFACE_HPP_
#define APPLICATION_USERINTERFACE_HPP_

#include "Common/Common.hpp"
#include "StringFormat/StringUtilities.hpp"

#include <string>

class Date;
class Time;

class UserInterface: public StringUtilities {
public:
	/* Input:
	 * fmt Formated buffer where the resulting string is stored.
	 * arg ... (additional arguments)
	 * Depending on the format string, the function may
	 * expect a sequence of additional arguments, each
	 * containing a value to be used to replace a format
	 * specifier in the format string (or a pointer to a storage location, for n).
	 * There should be at least as many of these arguments as the
	 * number of values specified in the format specifiers.
	 * Additional arguments are ignored by the function
	 */
	void display(const std::string fmt, ...);
	void displayResult(bool result);

	Date getDate();
	Time getTime();

	std::string getCompany();
	std::string getDepartureCity();
	std::string getArrivalCity();
	std::string getFirstName();
	std::string getSurname();
	uint64_t getPersonalId();
	uint32_t getFlightId();
	uint16_t getSeats();

	bool getRepeat();

	bool validateLength(const std::string & str, uint32_t length);

private:
	std::string getLine(uint32_t length);
	uint64_t getNumber(uint32_t length);
};

#endif /* APPLICATION_USERINTERFACE_HPP_ */
