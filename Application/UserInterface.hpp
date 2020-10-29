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

	std::string GetDate();

	//Ask user to enter detail and save this detail into dst string
	void RegisterRecord(std::string & dst, std::string output, uint32_t offset, uint32_t length);
};

#endif /* APPLICATION_USERINTERFACE_HPP_ */
