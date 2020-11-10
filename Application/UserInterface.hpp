/*
 * UserInterface.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_USERINTERFACE_HPP_
#define APPLICATION_USERINTERFACE_HPP_

#include "Common/Common.hpp"
#include "Common/StringUtilities.hpp"

#include <string>

class Date;
class Time;
class DateTime;

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
	void Display(const std::string fmt, ...);


	Date GetDate();
	Time GetTime();
	DateTime GetDateTime();

	std::string GetCompany();
	std::string GetDepartureCity();
	std::string GetArrivalCity();
	bool validateLength(const std::string & str, uint32_t length);

private:
	void getLine(std::string & dst, uint32_t length);
};

#endif /* APPLICATION_USERINTERFACE_HPP_ */
