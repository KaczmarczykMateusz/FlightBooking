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

	//Trim from end
	static inline void rtrimNewLine(std::string &s) {
	    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
	        return !(  (ch == '\n') || (ch == '\r')  );
	    }).base(), s.end());
	}

	static inline void toLower(std::string & s) {
		std::transform(s.begin(), s.end(), s.begin(),
			[](unsigned char c){ return std::tolower(c); });
	}
};



#endif /* APPLICATION_STRINGUTILITIES_HPP_ */
