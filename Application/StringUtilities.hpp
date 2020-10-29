/*
 * StringUtilities.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Matuesz Kaczmarczyk
 */

#ifndef APPLICATION_STRINGUTILITIES_HPP_
#define APPLICATION_STRINGUTILITIES_HPP_

#include <string>
#include <algorithm> //For base() etc

class StringUtilities {
public:

	//Trim from end
	static inline void rtrim(std::string &s) {
	    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
	        return !std::isspace(ch);
	    }).base(), s.end());
	}
};



#endif /* APPLICATION_STRINGUTILITIES_HPP_ */
